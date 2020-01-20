## cJSON学习篇

<span  style="color: #ff3d00; ">参考资料：</span>

[github资料](https://github.com/Miss1xiaobao/cJSON)

> https://github.com/Miss1xiaobao/cJSON

学习：    
1、如何调用CJSON的接口去处理需要传输的数据？ 2、接口的功能 3、字符串和CJSON链表的物理模型

#### 一、描述
1、cJSON功能： 移动数据、存储数据。  
2、<span  style="color: #AE87FA; ">cJSON.h文件描述：</span>

```c
/* The cJSON structure: */
typedef struct cJSON {
    struct cJSON *next, *prev; /* next/prev allow you to walk array/object chains. Alternatively, use GetArraySize/GetArrayItem/GetObjectItem */
    struct cJSON *child; /* An array or object item will have a child pointer pointing to a chain of the items in the array/object. */

    int type; /* The type of the item, as above. */

    char *valuestring; /* The item's string, if type==cJSON_String */
    int valueint; /* The item's number, if type==cJSON_Number */
    double valuedouble; /* The item's number, if type==cJSON_Number */

    char *string; /* The item's name string, if this item is the child of, or is in the list of subitems of an object. */
} cJSON;

/* Default options for cJSON_Parse */
// 默认选项解析cJSON
cJSON *cJSON_Parse(const char *value);  

/* Parse an object - create a new root, and populate. */
//解析一个object-创建一个新的root，然后填充。
cJSON *cJSON_ParseWithOpts(const char *value, const char **return_parse_end, int require_null_terminated);

/* Internal constructor. */
内部构造函数，申请一个cJSON结构体的内存。
static cJSON *cJSON_New_Item(void);

/* Parser core - when encountering text, process appropriately. */
解析器核心——遇到文本时，适当地处理
static const char *parse_value(cJSON *item, const char *value);

/* Utility to jump whitespace and cr/lf */
跳转 writespace 和 cr/lf 的实用程序；(ASCII字符编码小于等于32的字符)去掉；
static const char *skip(const char *in);

/* Build an object from the text. */
从文本构建一个object
static const char *parse_object(cJSON *item, const char *value)

/* Parse the input text into an unescaped cstring, and populate item. */
将输入的文本解析为未转义的字符串，填充
static const char *parse_string(cJSON *item, const char *str)

//

```

3、	函数接口

```c
解析器的核心
static const char *parse_value(cJSON *item, const char *value)
{
    if (!value) return 0; /* Fail on null. */
    if (!strncmp(value, "null", 4))
    {
        item->type = cJSON_NULL;
        return value + 4;
    }
    if (!strncmp(value, "false", 5))
    {
        item->type = cJSON_False;
        return value + 5;
    }
    if (!strncmp(value, "true", 4))
    {
        item->type = cJSON_True;
        item->valueint = 1;
        return value + 4;
    }
    if (*value == '\"')
    {
        return parse_string(item, value);
    }
    if (*value == '-' || (*value >= '0' && *value <= '9'))
    {
        return parse_number(item, value);
    }
    if (*value == '[')
    {
        return parse_array(item, value);
    }
    if (*value == '{')
    {
        return parse_object(item, value);
    }

    ep = value;
    return 0; /* failure. */
}

1、这里的value的类型是char *，“长度”是1个字符；

```

```
/* Parse the input text into an unescaped cstring, and populate item. */
将输入的文本解析为未转义的字符串。

static const char *parse_string(cJSON *item, const char *str)
{
    const char *ptr = str + 1;
    char *ptr2;
    char *out;
    int len = 0;
    unsigned uc, uc2;
    if (*str != '\"') {//判断这个str是不是“”字符串
        ep = str;
        return 0;
    } /* not a string! */

//len里面储存 ptr字符串 里面 字符的个数
//统计这个“”字符串里面有多少个字符。转义字符是一个字符
    while (*ptr != '\"' && *ptr && ++len)
        if (*ptr++ == '\\') ptr++; /* Skip escaped quotes. */

    out = (char*) cJSON_malloc(len + 1); /* This is how long we need for the string, roughly. */
    if (!out) return 0;

    ptr = str + 1;   //将指针指向这个“”字符串的开始位置
    ptr2 = out;   //将申请的内存空间的指针指向ptr2，这样只要向ptr2这个指针存储也就到了这个内存空间中。
    while (*ptr != '\"' && *ptr)
    {
        if (*ptr != '\\') *ptr2++ = *ptr++;  //不是转义字符就存储到malloc申请的内存空间。如果是转义字符，就去处理这个字符（转义字符的具体处理）
        else
        {
            ptr++;
            switch (*ptr)
            {
                case 'b':
                    *ptr2++ = '\b';
                    break;
                case 'f':
                    *ptr2++ = '\f';
                    break;
                case 'n':
                    *ptr2++ = '\n';
                    break;
                case 'r':
                    *ptr2++ = '\r';
                    break;
                case 't':
                    *ptr2++ = '\t';
                    break;
                case 'u': /* transcode utf16 to utf8. */
                    uc = parse_hex4(ptr + 1);
                    ptr += 4; /* get the unicode char. */

                    if ((uc >= 0xDC00 && uc <= 0xDFFF) || uc == 0) break; /* check for invalid.	*/

                    if (uc >= 0xD800 && uc <= 0xDBFF) /* UTF16 surrogate pairs.	*/
                    {
                        if (ptr[1] != '\\' || ptr[2] != 'u') break; /* missing second-half of surrogate.	*/
                        uc2 = parse_hex4(ptr + 3);
                        ptr += 6;
                        if (uc2 < 0xDC00 || uc2 > 0xDFFF) break; /* invalid second-half of surrogate.	*/
                        uc = 0x10000 + (((uc & 0x3FF) << 10) | (uc2 & 0x3FF));
                    }

                    len = 4;
                    if (uc < 0x80) len = 1;
                    else if (uc < 0x800) len = 2;
                    else if (uc < 0x10000) len = 3;
                    ptr2 += len;

                    switch (len)
                    {
                        case 4:
                            *--ptr2 = ((uc | 0x80) & 0xBF);
                            uc >>= 6;
                        case 3:
                            *--ptr2 = ((uc | 0x80) & 0xBF);
                            uc >>= 6;
                        case 2:
                            *--ptr2 = ((uc | 0x80) & 0xBF);
                            uc >>= 6;
                        case 1:
                            *--ptr2 = (uc | firstByteMark[len]);
                    }
                    ptr2 += len;
                    break;
                default:
                    *ptr2++ = *ptr;
                    break;
            }
            ptr++;
        }
    }
    *ptr2 = 0;
    if (*ptr == '\"') ptr++;
    item->valuestring = out;
    item->type = cJSON_String;
    return ptr;
}
```

#### 二、将 cJSON字符串 解析成 cJSON结构体链表

1、这是一个在程序中输入的字符串，然后去解析

```c
char *data = "{\"name\":\"Missbao\",\"age\":21,\"love\":[\"lol1\", \"lol2\"]}";

cJSON *root = cJSON_Parse(data);

printf("data:%s\n", cJSON_Print(root));
printf("data:%s\n", cJSON_PrintUnformatted(root));


运行结果：
data:{
        "name": "Missbao",
        "age":  21,
        "love": ["lol1", "lol2"]
}
data:{"name":"Missbao","age":21,"love":["lol1","lol2"]}
```

2、读取 外部文件中 的 cJSON字符串 解析

```c
cJSON字符串：
{"Version":"1.0.0","BasicInfo":{"btype":"克隆人","bname":"小豹","strings":["string1","string2","string3"]},"Property":{"name":"onOffStatus","dataType":"bool","variants":[{"stdValue":true,"eppValue":1},{"stdValue":false,"eppValue":0}]}}


{
    "Version":"1.0.0",
    "BasicInfo":{
        "btype":"克隆人",
        "bname":"小豹"
        "strings":[
            "string1",
            "string2",
            "string3"
        ]
    },
    "Property":{
            "name":"onOffStatus",
            "dataType":"bool",
            "variants":[
                {
                    "stdValue":true,
                    "eppValue":1
                },
                
                {
                    "stdValue":false,
                    "eppValue":0
                }
            ]
    }
}
```
解析后的cJSON结构体物理模型

>解析过程： 
>    
> - 1、parse_value(c, skip(value);     
>  > cJSON * c是新建的root，  const char * value是要解析的字符串
>     
> - 2、parse_object; 
>  > 构建 child 1， new item 1
>
> - 3、parse_object；
>  > 构建child2 ， new item 2， while循环构建 new item 3
> - 4、parse_array；
>  > child 3, 循环里面 new item 4，new item 5 
> - 5、返回 parse_object（3、）
>  > 返回到“BasicInfo” 的parse_object （2、）进入 循环 new item 6
> 
> 。。。。。


 见  cJSON解析结构体链表.png
 
 [cJSON解析结构体链表.png](https://blog.csdn.net/weixin_44966900/article/details/104054791)
 
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020012017490676.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NDk2NjkwMA==,size_16,color_FFFFFF,t_70) 

#### 三、将 cJSON结构体链表 转化为 字符串
1、<span  style="color: #AE87FA; ">cJSON.h文件描述：</span>

```c
/* Render a cJSON entity to text for transfer/storage. Free the char* when finished. */
将cJSON实体呈现为用于传输/存储的文本。完成后释放char*。
extern char *cJSON_Print(cJSON *item);

/* Render a cJSON entity to text for transfer/storage without any formatting. Free the char* when finished. */
将cJSON实体呈现为用于传输/存储的文本，而不进行任何格式化。完成后释放char*。
extern char *cJSON_PrintUnformatted(cJSON *item);




/* Returns the number of items in an array (or object). */
返回数组(或对象)中的项数
extern int cJSON_GetArraySize(cJSON *array);

/* Get item "string" from object. Case insensitive. */
从对象中获取项目“string”。不分大小写
extern cJSON *cJSON_GetObjectItem(cJSON *object, const char *string);

/* Delete a cJSON entity and all subentities. */
删除一个cJSON实体和所有子实体
extern void cJSON_Delete(cJSON *c);
```


#### 四、利用add接口构建一个cJSON结构体链表

```
	cJSON *c = cJSON_CreateObject();
    cJSON *c1 = cJSON_CreateObject();
    cJSON *array = cJSON_CreateArray();

    cJSON_AddItemToArray(array, cJSON_CreateString("string1"));
    cJSON_AddItemToArray(array, cJSON_CreateString("string2"));

    cJSON_AddStringToObject(c, "name", "Missbao");
    cJSON_AddNumberToObject(c, "age", 20);
    cJSON_AddBoolToObject(c, "boy", 1);
    cJSON_AddItemToObject(c, "love", array);
    cJSON_AddItemToObject(c, "work", c1);

    printf("%s\n", cJSON_Print(c));
    
运行结果：  
    
{
        "name": "Missbao",
        "age":  20,
        "boy":  true,
        "love": ["string1", "string2"],
        "work": {
}
}
```


2、<span  style="color: #AE87FA; ">cJSON.h文件描述：</span>

