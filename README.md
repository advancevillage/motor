## 代码风格

* 一般规则
  * 最长命名不超过80个字符,包括函数名,变量,宏定义,类型定义
    * 注意尾随没有空格
  * 缩进是一个tab
  * 16进制全部小写
  * 文件名,函数和全局变量具有kr_前缀
* 文件组成
  * 版权声明
  * include
  * 宏定义
  * 类型定义
  * 变量定义
  * 函数定义

```
/*
 * Copyright (C) Kelly & Richard
 * Copyright (C) kr, Inc
 */

#include <kr_config.h>
#include <kr_core.h>

#ifndef _KR_LOG_H_INCLUDE_
#define _KR_LOG_H_INCLUDE_

typedef struct kr_log_s kr_log_t;

struct kr_log_s {
    ...
};

...

#endif

```

* 注释

```
/**
 *@author  作者说明
 *@brief   简易说明
 *@param   参数说明
 *@return  返回值说明
 */
```

* 宏定义
  * 宏名前缀 kr_ 或 KR_
  * 常量宏定义大写
  * 参数化宏小写

```
#define KR_LOG_STDERR    0

#define kr_tolower(c)   (u_char) ((c >= 'A' && c <= 'Z') ? (c | 0x20) : c)
```

* 类型定义
  * 以 _t 后缀结尾

```
typedef struct kr_list_part_s  kr_list_part_t;

struct kr_list_part_s {
    void             *elts;
    kr_uint_t        nelts;
    kr_list_part_t   *next;
};
```

* 变量定义
  * 变量声明按基本类型的长度排序，然后按字母顺序排序
  * 类型名称和变量名称对齐
  * 大数组放在声明块的末尾
  * 静态和全局变量可以在声明时初始化

```
u_char                      |  | *rv, *p;
ngx_conf_t                  |  | *cf;
ngx_uint_t                  |  |  i, j, k;
unsigned int                |  |  len;
struct sockaddr             |  | *sa;
const unsigned char         |  | *data;
ngx_peer_connection_t       |  | *pc;
ngx_http_core_srv_conf_t    |  |**cscfp;
ngx_http_upstream_srv_conf_t|  | *us, *uscf;
u_char                      |  |  text[NGX_SOCKADDR_STRLEN];

static ngx_str_t  ngx_http_memcached_key = ngx_string("memcached_key");
static ngx_uint_t  mday[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
```

* 函数定义
  * 所有函数（甚至是静态函数）都应该有原型.原型包括参数名称

* 条件和循环
  * 注意空格和对齐

```
if (node->left == sentinel) {
    temp = node->right;
    subst = node;

} else if (node->right == sentinel) {
    temp = node->left;
    subst = node;

} else {
    subst = ngx_rbtree_min(node->right, sentinel);

    if (subst->left != sentinel) {
        temp = subst->left;

    } else {
        temp = subst->right;
    }
}

while (p < last && *p == ' ') {
    p++;
}
do {
    ctx->node = rn;
    ctx = ctx->next;
} while (ctx)

switch (ch) {
case '!':
    looked = 2;
    state = ssi_comment0_state;
    break;

case '<':
    copy_end = p;
    break;

default:
    copy_end = p;
    looked = 0;
    state = ssi_start_state;
    break;
}
```