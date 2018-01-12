#ifndef  COMPILERDEF_H_
#define  COMPILERDEF_H_


#define TABLEMAX 1024
#define MSG_LEN 256

#define CODEC_CHECK_RETURN(P)  if(!P){LogError("%s : %s invalid param, line:%d!",__FILE__, __FUNCTION__, __LINE__);return;}
#define CODEC_CHECK_WHILE(P)  if(!P){LogError("%s : %s invalid param, line:%d!",__FILE__, __FUNCTION__, __LINE__); Sleep(10);continue;}
#define CODEC_CHECK_RETURN_ERROR(P)  if(!P){LogError("%s : %s invalid param, line:%d!",__FILE__, __FUNCTION__, __LINE__); return ERROR_INVALID_PARAM;}
#define ZERO_MEMORY(VAR) {memset(&VAR, NULL, sizeof(VAR));}

#define ALIGN_SET 0x100  // 强制对齐标志

typedef enum {
	LEX_NORMAL = 0,
	LEX_LEP = 1
}scpLexState;

typedef enum {
	SCP_ERROR_NONE = 0,

	SCP_INVALID_PARAM = -1,
	SCP_POINTER_NULL = -2,
	SCP_MALLOC_FAILED = -3,
	SCP_OPEN_FAILED = -4,
	SCP_CLOSE_FAILED = -5,
	SCP_INIT_FAILED = -6



}scpStatus;

typedef enum {
	/* 运算符及分隔符 */
	TK_PLUS,		// + 加号
	TK_MINUS,		// - 减号
	TK_STAR,		// * 星号
	TK_DIVIDE,		// / 除号
	TK_MOD,			// % 求余运算符
	TK_EQ,			// == 等于号
	TK_NEQ,			// != 不等于号
	TK_LT,			// < 小于号
	TK_LEQ,			// <= 小于等于号
	TK_GT,			// > 大于号
	TK_GEQ,			// >= 大于等于号
	TK_ASSIGN,		// = 赋值运算符 
	TK_POINTSTO,	// -> 指向结构体成员运算符
	TK_DOT,			// . 结构体成员运算符
	TK_AND,         // & 地址与运算符
	TK_OPENPA,		// ( 左圆括号
	TK_CLOSEPA,		// ) 右圆括号
	TK_OPENBR,		// [ 左中括号
	TK_CLOSEBR,		// ] 右圆括号
	TK_BEGIN,		// { 左大括号
	TK_END,			// } 右大括号
	TK_SEMICOLON,	// ; 分号    
	TK_COMMA,		// , 逗号
	TK_ELLIPSIS,	// ... 省略号
	TK_EOF,			// 文件结束符

	/* 常量 */
	TK_CINT,		// 整型常量
	TK_CCHAR,		// 字符常量
	TK_CSTR,		// 字符串常量

	/* 关键字 */
	KW_CHAR,		// char关键字
	KW_SHORT,		// short关键字
	KW_INT,			// int关键字
	KW_BOOL,		// bool关键字
	KW_VOID,		// void关键字  
	KW_STRUCT,		// struct关键字   
	KW_IF,			// if关键字
	KW_ELSE,		// else关键字
	KW_FOR,			// for关键字
	KW_CONTINUE,	// continue关键字
	KW_BREAK,		// break关键字   
	KW_RETURN,		// return关键字
	KW_SIZEOF,		// sizeof关键字

	KW_ALIGN,		// __align关键字	
	KW_CDECL,		// __cdecl关键字 standard c call
	KW_STDCALL,     // __stdcall关键字 pascal c call

	/* 标识符 */
	TK_IDENT
}eTokenCode;

/* 存储类型 */
typedef enum {
	SC_GLOBAL = 0x00f0,		// 包括：包括整型常量，字符常量、字符串常量,全局变量,函数定义          
	SC_LOCAL = 0x00f1,		// 栈中变量
	SC_LLOCAL = 0x00f2,       // 寄存器溢出存放栈中
	SC_CMP = 0x00f3,       // 使用标志寄存器
	SC_VALMASK = 0x00ff,       // 存储类型掩码             
	SC_LVAL = 0x0100,       // 左值       
	SC_SYM = 0x0200,       // 符号	

	SC_ANOM = 0x10000000,     // 匿名符号
	SC_STRUCT = 0x20000000,     // 结构体符号
	SC_MEMBER = 0x40000000,     // 结构成员变量
	SC_PARAMS = 0x80000000,     // 函数参数
}e_VarType;

/* 类型编码 */
typedef enum
{
	T_INT = 0,			// 整型                     
	T_CHAR = 1,			// 字符型                 
	T_SHORT = 2,			// 短整型                       
	T_VOID = 3,			// 空类型                        
	T_PTR = 4,			// 指针                          
	T_FUNC = 5,			// 函数                    
	T_STRUCT = 6,			// 结构体 

	T_BTYPE = 0x000f,		// 基本类型掩码          
	T_ARRAY = 0x0010,		// 数组
}e_TypeCode;

/*语法状态*/
typedef enum {
	SC_STATE_NULL = 0,		//空状态，没有语法缩进
	SC_STATE_SP = 1,		//空格	
	SC_STATE_LF_HT = 2,     //换行并缩进，每一个声明、函数定义、语句结束都要置为此状态
	SC_STATE_DELAY = 3		//延迟到取出下一单词后确定输出格式

}e_SynState;

template<typename T>
inline void safe_release(T **p, bool b_block)
{
	if (*p)
	{
		if (b_block)
			delete[](*p);
		else
			delete (*p);
		*p = NULL;
	}
}

template<typename T>
inline  T *rd_malloc(unsigned int size)
{
	T *p = NULL;
	try
	{
		if (size)
			p = new T[size];
		else
			p = new T;
	}
	catch (const std::bad_alloc& e)
	{
		//LogError("%s : %s malloc error:%s, line:%d!", __FILE__, __FUNCTION__, e.what(), __LINE__);
	}
	return p;
}

template<typename T>
inline  T *rd_malloc_class(void *reserverd)
{
	T *p = NULL;
	try
	{
		p = new T(reserverd);
	}
	catch (const std::bad_alloc& e)
	{
		//LogError("%s : %s malloc error:%s, line:%d!", __FILE__, __FUNCTION__, e.what(), __LINE__);
	}
	return p;
}



template<typename T>
struct _SmartString
{
	int size;//length of string
	int capacity;//the capacity of buffer
	T *data;
};


template<typename T>
struct _SmartArray {
	int size;//length of array
	int capacity;//the capacity of buffer
	T **data;

};

/* 类型存储结构定义 */
typedef struct Type
{
	int t;
	struct Symbol *ref;
} Type;

/* 符号存储结构定义 */
typedef struct Symbol
{
	int token;					// 符号的单词编码
	int reg;					// 符号关联的寄存器
	int value;						// 符号关联值
	Type type;					// 符号类型
	struct Symbol *next;		// 关联的其它符号，结构体定义关联成员变量符号，函数定义关联参数符号
	struct Symbol *prev_tok;	// 指向前一定义的同名符号
} Symbol;

typedef struct _Tk_Word {
	int tkcode;//word code						// 单词编码 
	struct _Tk_Word *next;//conflict word		// 指向哈希冲突的其它单词
	char *p_word;//word sring					// 单词字符串 
	struct Symbol *sym_struct;					// 指向单词所表示的结构定义
	struct Symbol *sym_identifier;				// 指向单词所表示的标识符

}_TkWord;


static _TkWord keywords[] = {
	{ TK_PLUS,		NULL	,"+",					NULL,	NULL },
	{ TK_MINUS,		NULL	,"-",					NULL,	NULL },
	{ TK_STAR,		NULL	,"*",					NULL,	NULL },
	{ TK_DIVIDE,	NULL	,"/",					NULL,	NULL },
	{ TK_MOD,		NULL	,"%",					NULL,	NULL },
	{ TK_EQ,		NULL	,"==",					NULL,	NULL },
	{ TK_NEQ,		NULL	,"!=",					NULL,	NULL },
	{ TK_LT,		NULL	,"<",					NULL,	NULL },
	{ TK_LEQ,		NULL	,"<=",					NULL,	NULL },
	{ TK_GT,		NULL	,">",					NULL,	NULL },
	{ TK_GEQ,		NULL	,">=",					NULL,	NULL },
	{ TK_ASSIGN,	NULL	,"=",					NULL,	NULL },
	{ TK_POINTSTO,	NULL	,"->",					NULL,	NULL },
	{ TK_DOT,		NULL	,".",					NULL,	NULL },
	{ TK_AND,		NULL	,"&",					NULL,	NULL },
	{ TK_OPENPA,	NULL	,"(",					NULL,	NULL },
	{ TK_CLOSEPA,	NULL	,")",					NULL,	NULL },
	{ TK_OPENBR,	NULL	,"[",					NULL,	NULL },
	{ TK_CLOSEBR,	NULL	,"]",					NULL,	NULL },
	{ TK_BEGIN,		NULL	,"{",					NULL,	NULL },
	{ TK_END,		NULL	,"}",					NULL,	NULL },
	{ TK_SEMICOLON,	NULL	,";",					NULL,	NULL },
	{ TK_COMMA,		NULL	,",",					NULL,	NULL },
	{ TK_ELLIPSIS,	NULL	,"...",					NULL,	NULL },
	{ TK_EOF,		NULL	,"End_Of_File",			NULL,	NULL },
	{ TK_CINT,		NULL	,"Integer Constant",	NULL,	NULL },
	{ TK_CCHAR,		NULL	,"Character Constant",	NULL,	NULL },
	{ TK_CSTR,		NULL	,"String Constants",	NULL,	NULL },
	{ KW_CHAR,		NULL	,"char",				NULL,	NULL },
	{ KW_SHORT,		NULL	,"short",				NULL,	NULL },
	{ KW_INT,		NULL	,"int",					NULL,	NULL },
	{ KW_BOOL,		NULL	,"bool",				NULL,	NULL },
	{ KW_VOID,		NULL	,"void",				NULL,	NULL },
	{ KW_STRUCT,	NULL	,"struct",				NULL,	NULL },
	{ KW_IF,		NULL	,"if",					NULL,	NULL },
	{ KW_ELSE,		NULL	,"else",				NULL,	NULL },
	{ KW_FOR,		NULL	,"for",					NULL,	NULL },
	{ KW_CONTINUE,	NULL	,"continue",			NULL,	NULL },
	{ KW_BREAK,		NULL	,"break",				NULL,	NULL },
	{ KW_RETURN,	NULL	,"return",				NULL,	NULL },
	{ KW_SIZEOF,	NULL	,"sizeof",				NULL,	NULL },
	{ KW_ALIGN,		NULL	,"__align",				NULL,	NULL },
	{ KW_CDECL,		NULL	,"__cdecl",				NULL,	NULL },
	{ KW_STDCALL,	NULL	,"__stdcall",			NULL,	NULL },
	{ 0,			NULL	,NULL,					NULL,	NULL },
};


#endif // ! COMPILERDEF_H_

