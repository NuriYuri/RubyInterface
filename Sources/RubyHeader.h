#pragma once
//===
//Header de définition des macro et structures du ruby
//===
#include "RubyAlias.h"

enum ruby_special_consts {
    RUBY_Qfalse = 0,
    RUBY_Qtrue  = 2,
    RUBY_Qnil   = 4,
    RUBY_Qundef = 6,

    RUBY_IMMEDIATE_MASK = 0x03,
    RUBY_FIXNUM_FLAG    = 0x01,
    RUBY_FLONUM_MASK    = 0x00,	/* any values ANDed with FLONUM_MASK cannot be FLONUM_FLAG */
    RUBY_FLONUM_FLAG    = 0x02,
    RUBY_SYMBOL_FLAG    = 0x0e,
    RUBY_SPECIAL_SHIFT  = 8
};

#define Qfalse ((VALUE)RUBY_Qfalse)
#define Qtrue  ((VALUE)RUBY_Qtrue)
#define Qnil   ((VALUE)RUBY_Qnil)
#define Qundef ((VALUE)RUBY_Qundef)	/* undefined value for placeholder */
#define IMMEDIATE_MASK RUBY_IMMEDIATE_MASK
#define FIXNUM_FLAG RUBY_FIXNUM_FLAG
#define SYMBOL_FLAG RUBY_SYMBOL_FLAG
#define FLONUM_MASK RUBY_FLONUM_MASK
#define FLONUM_FLAG RUBY_FLONUM_FLAG

#define RTEST(v) !(((VALUE)(v) & ~Qnil) == 0)
#define NIL_P(v) !((VALUE)(v) != Qnil)
#define CLASS_OF(v) rb_class_of((VALUE)(v))

#define IMMEDIATE_P(x) ((VALUE)(x) & IMMEDIATE_MASK)

#define SYMBOL_P(x) (((VALUE)(x)&~(~(VALUE)0<<RUBY_SPECIAL_SHIFT))==SYMBOL_FLAG)
#define ID2SYM(x) (((VALUE)(x)<<RUBY_SPECIAL_SHIFT)|SYMBOL_FLAG)
#define SYM2ID(x) RSHIFT((unsigned long)(x),RUBY_SPECIAL_SHIFT)
#define FLONUM_P(x) ((((int)(VALUE)(x))&FLONUM_MASK) == FLONUM_FLAG)
#define FIXNUM_P(f) (((int)(VALUE)(f))&FIXNUM_FLAG)

enum ruby_value_type {
    RUBY_T_NONE   = 0x00,

    RUBY_T_OBJECT = 0x01,
    RUBY_T_CLASS  = 0x02,
    RUBY_T_MODULE = 0x03,
    RUBY_T_FLOAT  = 0x04,
    RUBY_T_STRING = 0x05,
    RUBY_T_REGEXP = 0x06,
    RUBY_T_ARRAY  = 0x07,
    RUBY_T_HASH   = 0x08,
    RUBY_T_STRUCT = 0x09,
    RUBY_T_BIGNUM = 0x0a,
    RUBY_T_FILE   = 0x0b,
    RUBY_T_DATA   = 0x0c,
    RUBY_T_MATCH  = 0x0d,
    RUBY_T_COMPLEX  = 0x0e,
    RUBY_T_RATIONAL = 0x0f,

    RUBY_T_NIL    = 0x11,
    RUBY_T_TRUE   = 0x12,
    RUBY_T_FALSE  = 0x13,
    RUBY_T_SYMBOL = 0x14,
    RUBY_T_FIXNUM = 0x15,

    RUBY_T_UNDEF  = 0x1b,
    RUBY_T_NODE   = 0x1c,
    RUBY_T_ICLASS = 0x1d,
    RUBY_T_ZOMBIE = 0x1e,

    RUBY_T_MASK   = 0x1f
};

#define T_NONE   RUBY_T_NONE
#define T_NIL    RUBY_T_NIL
#define T_OBJECT RUBY_T_OBJECT
#define T_CLASS  RUBY_T_CLASS
#define T_ICLASS RUBY_T_ICLASS
#define T_MODULE RUBY_T_MODULE
#define T_FLOAT  RUBY_T_FLOAT
#define T_STRING RUBY_T_STRING
#define T_REGEXP RUBY_T_REGEXP
#define T_ARRAY  RUBY_T_ARRAY
#define T_HASH   RUBY_T_HASH
#define T_STRUCT RUBY_T_STRUCT
#define T_BIGNUM RUBY_T_BIGNUM
#define T_FILE   RUBY_T_FILE
#define T_FIXNUM RUBY_T_FIXNUM
#define T_TRUE   RUBY_T_TRUE
#define T_FALSE  RUBY_T_FALSE
#define T_DATA   RUBY_T_DATA
#define T_MATCH  RUBY_T_MATCH
#define T_SYMBOL RUBY_T_SYMBOL
#define T_RATIONAL RUBY_T_RATIONAL
#define T_COMPLEX RUBY_T_COMPLEX
#define T_UNDEF  RUBY_T_UNDEF
#define T_NODE   RUBY_T_NODE
#define T_ZOMBIE RUBY_T_ZOMBIE
#define T_MASK   RUBY_T_MASK

#define BUILTIN_TYPE(x) (int)(((struct RBasic*)(x))->flags & T_MASK)
static inline int rb_type(VALUE obj);
#define TYPE(x) rb_type((VALUE)(x))
#define Check_Type(v,t) rb_check_type((VALUE)(v),(t))


//Structures du ruby
struct RBasic {
    VALUE flags;
    VALUE klass;
};

#define ROBJECT_EMBED_LEN_MAX 3
struct RObject {
    struct RBasic basic;
    union {
	struct {
	    long numiv;
	    VALUE *ivptr;
		struct st_table *iv_index_tbl; /* shortcut for RCLASS_IV_INDEX_TBL(rb_obj_class(obj)) */
	} heap;
	VALUE ary[ROBJECT_EMBED_LEN_MAX];
    } as;
};

#define ROBJECT_EMBED FL_USER1
#define ROBJECT_NUMIV(o) \
    ((RBASIC(o)->flags & ROBJECT_EMBED) ? \
     ROBJECT_EMBED_LEN_MAX : \
     ROBJECT(o)->as.heap.numiv)
#define ROBJECT_IVPTR(o) \
    ((RBASIC(o)->flags & ROBJECT_EMBED) ? \
     ROBJECT(o)->as.ary : \
     ROBJECT(o)->as.heap.ivptr)
#define ROBJECT_IV_INDEX_TBL(o) \
    ((RBASIC(o)->flags & ROBJECT_EMBED) ? \
     RCLASS_IV_INDEX_TBL(rb_obj_class(o)) : \
     ROBJECT(o)->as.heap.iv_index_tbl)

typedef struct rb_classext_struct rb_classext_t;

struct RClass {
    struct RBasic basic;
    rb_classext_t *ptr;
    struct st_table *m_tbl;
    struct st_table *iv_index_tbl;
};
#define RCLASS_SUPER(c) rb_class_get_superclass(c)
#define RMODULE_IV_TBL(m) RCLASS_IV_TBL(m)
#define RMODULE_CONST_TBL(m) RCLASS_CONST_TBL(m)
#define RMODULE_M_TBL(m) RCLASS_M_TBL(m)
#define RMODULE_SUPER(m) RCLASS_SUPER(m)
#define RMODULE_IS_OVERLAID FL_USER2
#define RMODULE_IS_REFINEMENT FL_USER3
#define RMODULE_INCLUDED_INTO_REFINEMENT FL_USER4

struct RFloat {
    struct RBasic basic;
    double float_value;
};
static inline double rb_float_value(VALUE v)
{
    return ((struct RFloat *)v)->float_value;
}
static inline VALUE rb_float_new(double d)
{
    return rb_float_new_in_heap(d);
}
#define RFLOAT_VALUE(v) rb_float_value(v)
#define DBL2NUM(dbl)  rb_float_new(dbl)


#define ELTS_SHARED FL_USER2

#define RSTRING_EMBED_LEN_MAX ((int)((sizeof(VALUE)*3)/sizeof(char)-1))
struct RString {
    struct RBasic basic;
    union {
		struct {
			long len;
			char *ptr;
			union {
				long capa;
				VALUE shared;
			} aux;
		} heap;
		char ary[RSTRING_EMBED_LEN_MAX + 1];
	} as;
};
#define RSTRING_NOEMBED FL_USER1
#define RSTRING_EMBED_LEN_MASK (FL_USER2|FL_USER3|FL_USER4|FL_USER5|FL_USER6)
#define RSTRING_EMBED_LEN_SHIFT (FL_USHIFT+2)
#define RSTRING_EMBED_LEN(str) \
     (long)((RBASIC(str)->flags >> RSTRING_EMBED_LEN_SHIFT) & \
            (RSTRING_EMBED_LEN_MASK >> RSTRING_EMBED_LEN_SHIFT))
#define RSTRING_LEN(str) \
    (!(RBASIC(str)->flags & RSTRING_NOEMBED) ? \
     RSTRING_EMBED_LEN(str) : \
     RSTRING(str)->as.heap.len)
#define RSTRING_PTR(str) \
    (!(RBASIC(str)->flags & RSTRING_NOEMBED) ? \
     RSTRING(str)->as.ary : \
     RSTRING(str)->as.heap.ptr)
#define RSTRING_END(str) \
    (!(RBASIC(str)->flags & RSTRING_NOEMBED) ? \
     (RSTRING(str)->as.ary + RSTRING_EMBED_LEN(str)) : \
     (RSTRING(str)->as.heap.ptr + RSTRING(str)->as.heap.len))
#define RSTRING_LENINT(str) rb_long2int(RSTRING_LEN(str))
#define RSTRING_GETMEM(str, ptrvar, lenvar) \
    (!(RBASIC(str)->flags & RSTRING_NOEMBED) ? \
     ((ptrvar) = RSTRING(str)->as.ary, (lenvar) = RSTRING_EMBED_LEN(str)) : \
     ((ptrvar) = RSTRING(str)->as.heap.ptr, (lenvar) = RSTRING(str)->as.heap.len))

#define RARRAY_EMBED_LEN_MAX 3
struct RArray {
    struct RBasic basic;
    union {
		struct {
			long len;
			union {
				long capa;
				VALUE shared;
			} aux;
			VALUE *ptr;
		} heap;
		VALUE ary[RARRAY_EMBED_LEN_MAX];
	} as;
};
#define RARRAY_EMBED_FLAG FL_USER1
/* FL_USER2 is for ELTS_SHARED */
#define RARRAY_EMBED_LEN_MASK (FL_USER4|FL_USER3)
#define RARRAY_EMBED_LEN_SHIFT (FL_USHIFT+3)
#define RARRAY_LEN(a) \
    ((RBASIC(a)->flags & RARRAY_EMBED_FLAG) ? \
     (long)((RBASIC(a)->flags >> RARRAY_EMBED_LEN_SHIFT) & \
	 (RARRAY_EMBED_LEN_MASK >> RARRAY_EMBED_LEN_SHIFT)) : \
     RARRAY(a)->as.heap.len)
#define RARRAY_PTR(a) \
    ((RBASIC(a)->flags & RARRAY_EMBED_FLAG) ? \
     RARRAY(a)->as.ary : \
     RARRAY(a)->as.heap.ptr)
#define RARRAY_LENINT(ary) rb_long2int(RARRAY_LEN(ary))

struct RRegexp {
    struct RBasic basic;
    struct re_pattern_buffer *ptr;
    VALUE src;
    unsigned long usecnt;
};
#define RREGEXP_SRC(r) RREGEXP(r)->src
#define RREGEXP_SRC_PTR(r) RSTRING_PTR(RREGEXP(r)->src)
#define RREGEXP_SRC_LEN(r) RSTRING_LEN(RREGEXP(r)->src)
#define RREGEXP_SRC_END(r) RSTRING_END(RREGEXP(r)->src)

struct RHash {
    struct RBasic basic;
    struct st_table *ntbl;      /* possibly 0 */
    int iter_lev;
    VALUE ifnone;
};
/* RHASH_TBL allocates st_table if not available. */
#define RHASH_TBL(h) rb_hash_tbl(h)
#define RHASH_ITER_LEV(h) (RHASH(h)->iter_lev)
#define RHASH_IFNONE(h) (RHASH(h)->ifnone)
#define RHASH_SIZE(h) (RHASH(h)->ntbl ? RHASH(h)->ntbl->num_entries : 0)
#define RHASH_EMPTY_P(h) (RHASH_SIZE(h) == 0)

struct RFile {
    struct RBasic basic;
    struct rb_io_t *fptr;
};

struct RRational {
    struct RBasic basic;
    VALUE num;
    VALUE den;
};

struct RComplex {
    struct RBasic basic;
    VALUE real;
    VALUE imag;
};

struct RData {
    struct RBasic basic;
    void (*dmark)(void*);
    void (*dfree)(void*);
    void *data;
};

typedef struct rb_data_type_struct rb_data_type_t;

struct rb_data_type_struct {
    const char *wrap_struct_name;
    struct {
	void (*dmark)(void*);
	void (*dfree)(void*);
	size_t (*dsize)(const void *);
	void *reserved[2]; /* For future extension.
			      This array *must* be filled with ZERO. */
    } function;
    const rb_data_type_t *parent;
    void *data;        /* This area can be used for any purpose
                          by a programmer who define the type. */
};

#define HAVE_TYPE_RB_DATA_TYPE_T 1
#define HAVE_RB_DATA_TYPE_T_FUNCTION 1
#define HAVE_RB_DATA_TYPE_T_PARENT 1

struct RTypedData {
    struct RBasic basic;
    const rb_data_type_t *type;
    VALUE typed_flag; /* 1 or not */
    void *data;
};

#define DATA_PTR(dta) (RDATA(dta)->data)

#define RTYPEDDATA_P(v)    (RTYPEDDATA(v)->typed_flag == 1)
#define RTYPEDDATA_TYPE(v) (RTYPEDDATA(v)->type)
#define RTYPEDDATA_DATA(v) (RTYPEDDATA(v)->data)

typedef void (*RUBY_DATA_FUNC)(void*);

//#define Check_TypedStruct(v,t) rb_check_typeddata((VALUE)(v),(t))
#define RUBY_DEFAULT_FREE ((RUBY_DATA_FUNC)-1)
#define RUBY_NEVER_FREE   ((RUBY_DATA_FUNC)0)
#define RUBY_TYPED_DEFAULT_FREE RUBY_DEFAULT_FREE
#define RUBY_TYPED_NEVER_FREE   RUBY_NEVER_FREE

#define Data_Wrap_Struct(klass,mark,free,sval)\
    rb_data_object_alloc((klass),(sval),(RUBY_DATA_FUNC)(mark),(RUBY_DATA_FUNC)(free))

#define Data_Make_Struct(klass,type,mark,free,sval) (\
    (sval) = ALLOC(type),\
    memset((sval), 0, sizeof(type)),\
    Data_Wrap_Struct((klass),(mark),(free),(sval))\
)

#define Data_Get_Struct(obj,type,sval) do {\
    Check_Type((obj), T_DATA); \
    (sval) = (type*)DATA_PTR(obj);\
} while (0)

#define RSTRUCT_EMBED_LEN_MAX 3
struct RStruct {
    struct RBasic basic;
    union {
		struct {
			long len;
			VALUE *ptr;
		} heap;
		VALUE ary[RSTRUCT_EMBED_LEN_MAX];
	} as;
};
#define RSTRUCT_EMBED_LEN_MASK (FL_USER2|FL_USER1)
#define RSTRUCT_EMBED_LEN_SHIFT (FL_USHIFT+1)
#define RSTRUCT_LEN(st) \
    ((RBASIC(st)->flags & RSTRUCT_EMBED_LEN_MASK) ? \
     (long)((RBASIC(st)->flags >> RSTRUCT_EMBED_LEN_SHIFT) & \
            (RSTRUCT_EMBED_LEN_MASK >> RSTRUCT_EMBED_LEN_SHIFT)) : \
     RSTRUCT(st)->as.heap.len)
#define RSTRUCT_PTR(st) \
    ((RBASIC(st)->flags & RSTRUCT_EMBED_LEN_MASK) ? \
     RSTRUCT(st)->as.ary : \
     RSTRUCT(st)->as.heap.ptr)
//#define RSTRUCT_LENINT(st) rb_long2int(RSTRUCT_LEN(st))

typedef unsigned char BDIGIT;
#define RBIGNUM_EMBED_LEN_MAX ((int)((sizeof(VALUE)*3)/sizeof(BDIGIT)))
struct RBignum {
    struct RBasic basic;
    union {
        struct {
            long len;
            BDIGIT *digits;
        } heap;
        BDIGIT ary[RBIGNUM_EMBED_LEN_MAX];
    } as;
};
#define RBIGNUM_SIGN_BIT FL_USER1
/* sign: positive:1, negative:0 */
#define RBIGNUM_SIGN(b) ((RBASIC(b)->flags & RBIGNUM_SIGN_BIT) != 0)
#define RBIGNUM_SET_SIGN(b,sign) \
  ((sign) ? (RBASIC(b)->flags |= RBIGNUM_SIGN_BIT) \
          : (RBASIC(b)->flags &= ~RBIGNUM_SIGN_BIT))
#define RBIGNUM_POSITIVE_P(b) RBIGNUM_SIGN(b)
#define RBIGNUM_NEGATIVE_P(b) (!RBIGNUM_SIGN(b))

#define RBIGNUM_EMBED_FLAG FL_USER2
#define RBIGNUM_EMBED_LEN_MASK (FL_USER5|FL_USER4|FL_USER3)
#define RBIGNUM_EMBED_LEN_SHIFT (FL_USHIFT+3)
#define RBIGNUM_LEN(b) \
    ((RBASIC(b)->flags & RBIGNUM_EMBED_FLAG) ? \
     (long)((RBASIC(b)->flags >> RBIGNUM_EMBED_LEN_SHIFT) & \
            (RBIGNUM_EMBED_LEN_MASK >> RBIGNUM_EMBED_LEN_SHIFT)) : \
     RBIGNUM(b)->as.heap.len)
/* LSB:RBIGNUM_DIGITS(b)[0], MSB:RBIGNUM_DIGITS(b)[RBIGNUM_LEN(b)-1] */
#define RBIGNUM_DIGITS(b) \
    ((RBASIC(b)->flags & RBIGNUM_EMBED_FLAG) ? \
     RBIGNUM(b)->as.ary : \
     RBIGNUM(b)->as.heap.digits)
//#define RBIGNUM_LENINT(b) rb_long2int(RBIGNUM_LEN(b))

#define R_CAST(st)   (struct st*)
#define RBASIC(obj)  (R_CAST(RBasic)(obj))
#define ROBJECT(obj) (R_CAST(RObject)(obj))
#define RCLASS(obj)  (R_CAST(RClass)(obj))
#define RMODULE(obj) RCLASS(obj)
#define RFLOAT(obj)  (R_CAST(RFloat)(obj))
#define RSTRING(obj) (R_CAST(RString)(obj))
#define RREGEXP(obj) (R_CAST(RRegexp)(obj))
#define RARRAY(obj)  (R_CAST(RArray)(obj))
#define RHASH(obj)   (R_CAST(RHash)(obj))
#define RDATA(obj)   (R_CAST(RData)(obj))
#define RTYPEDDATA(obj)   (R_CAST(RTypedData)(obj))
#define RSTRUCT(obj) (R_CAST(RStruct)(obj))
#define RBIGNUM(obj) (R_CAST(RBignum)(obj))
#define RFILE(obj)   (R_CAST(RFile)(obj))
#define RRATIONAL(obj) (R_CAST(RRational)(obj))
#define RCOMPLEX(obj) (R_CAST(RComplex)(obj))

#define FL_SINGLETON FL_USER0
#define FL_RESERVED1 (((VALUE)1)<<5)
#define FL_RESERVED2 (((VALUE)1)<<6) /* will be used in the future GC */
#define FL_FINALIZE  (((VALUE)1)<<7)
#define FL_TAINT     (((VALUE)1)<<8)
#define FL_UNTRUSTED (((VALUE)1)<<9)
#define FL_EXIVAR    (((VALUE)1)<<10)
#define FL_FREEZE    (((VALUE)1)<<11)

#define FL_USHIFT    12

#define FL_USER0     (((VALUE)1)<<(FL_USHIFT+0))
#define FL_USER1     (((VALUE)1)<<(FL_USHIFT+1))
#define FL_USER2     (((VALUE)1)<<(FL_USHIFT+2))
#define FL_USER3     (((VALUE)1)<<(FL_USHIFT+3))
#define FL_USER4     (((VALUE)1)<<(FL_USHIFT+4))
#define FL_USER5     (((VALUE)1)<<(FL_USHIFT+5))
#define FL_USER6     (((VALUE)1)<<(FL_USHIFT+6))
#define FL_USER7     (((VALUE)1)<<(FL_USHIFT+7))
#define FL_USER8     (((VALUE)1)<<(FL_USHIFT+8))
#define FL_USER9     (((VALUE)1)<<(FL_USHIFT+9))
#define FL_USER10    (((VALUE)1)<<(FL_USHIFT+10))
#define FL_USER11    (((VALUE)1)<<(FL_USHIFT+11))
#define FL_USER12    (((VALUE)1)<<(FL_USHIFT+12))
#define FL_USER13    (((VALUE)1)<<(FL_USHIFT+13))
#define FL_USER14    (((VALUE)1)<<(FL_USHIFT+14))
#define FL_USER15    (((VALUE)1)<<(FL_USHIFT+15))
#define FL_USER16    (((VALUE)1)<<(FL_USHIFT+16))
#define FL_USER17    (((VALUE)1)<<(FL_USHIFT+17))
#define FL_USER18    (((VALUE)1)<<(FL_USHIFT+18))
#define FL_USER19    (((VALUE)1)<<(FL_USHIFT+19))

#define SPECIAL_CONST_P(x) (IMMEDIATE_P(x) || !RTEST(x))

#define FL_ABLE(x) (!SPECIAL_CONST_P(x) && BUILTIN_TYPE(x) != T_NODE)
#define FL_TEST(x,f) (FL_ABLE(x)?(RBASIC(x)->flags&(f)):0)
#define FL_ANY(x,f) FL_TEST((x),(f))
#define FL_ALL(x,f) (FL_TEST((x),(f)) == (f))
#define FL_SET(x,f) do {if (FL_ABLE(x)) RBASIC(x)->flags |= (f);} while (0)
#define FL_UNSET(x,f) do {if (FL_ABLE(x)) RBASIC(x)->flags &= ~(f);} while (0)
#define FL_REVERSE(x,f) do {if (FL_ABLE(x)) RBASIC(x)->flags ^= (f);} while (0)

#define OBJ_TAINTED(x) (!!FL_TEST((x), FL_TAINT))
#define OBJ_TAINT(x) FL_SET((x), FL_TAINT)
#define OBJ_UNTRUSTED(x) (!!FL_TEST((x), FL_UNTRUSTED))
#define OBJ_UNTRUST(x) FL_SET((x), FL_UNTRUSTED)
#define OBJ_INFECT(x,s) do { \
  if (FL_ABLE(x) && FL_ABLE(s)) \
    RBASIC(x)->flags |= RBASIC(s)->flags & \
                        (FL_TAINT | FL_UNTRUSTED); \
} while (0)

#define OBJ_FROZEN(x) (!!(FL_ABLE(x)?(RBASIC(x)->flags&(FL_FREEZE)):(FIXNUM_P(x)||FLONUM_P(x))))
#define OBJ_FREEZE(x) FL_SET((x), FL_FREEZE)

static inline VALUE rb_class_of(VALUE obj)
{
    if (IMMEDIATE_P(obj)) 
	{
		if (FIXNUM_P(obj)) return rb_cFixnum;
		if (FLONUM_P(obj)) return rb_cFloat;
		if (obj == Qtrue)  return rb_cTrueClass;
		if (SYMBOL_P(obj)) return rb_cSymbol;
	}
    else if (!RTEST(obj)) 
	{
		if (obj == Qnil)   return rb_cNilClass;
		if (obj == Qfalse) return rb_cFalseClass;
	}
	return RBASIC(obj)->klass;
}

static inline int rb_type(VALUE obj)
{
    if (IMMEDIATE_P(obj)) 
	{
		if (FIXNUM_P(obj)) return T_FIXNUM;
		if (FLONUM_P(obj)) return T_FLOAT;
		if (obj == Qtrue)  return T_TRUE;
		if (SYMBOL_P(obj)) return T_SYMBOL;
		if (obj == Qundef) return T_UNDEF;
	}
	else if (!RTEST(obj)) 
	{
		if (obj == Qnil)   return T_NIL;
		if (obj == Qfalse) return T_FALSE;
    }
	return BUILTIN_TYPE(obj);
}

#define RB_FLOAT_TYPE_P(obj) (FLONUM_P(obj) || (!SPECIAL_CONST_P(obj) && BUILTIN_TYPE(obj) == T_FLOAT))

#define RB_TYPE_P(obj, type) ( \
	((type) == T_FIXNUM) ? FIXNUM_P(obj) : \
	((type) == T_TRUE) ? ((obj) == Qtrue) : \
	((type) == T_FALSE) ? ((obj) == Qfalse) : \
	((type) == T_NIL) ? ((obj) == Qnil) : \
	((type) == T_UNDEF) ? ((obj) == Qundef) : \
	((type) == T_SYMBOL) ? SYMBOL_P(obj) : \
        ((type) == T_FLOAT) ? RB_FLOAT_TYPE_P(obj) : \
	(!SPECIAL_CONST_P(obj) && BUILTIN_TYPE(obj) == (type)))

typedef unsigned long st_data_t;
typedef struct st_table st_table;
typedef st_data_t st_index_t;
typedef st_index_t st_hash_func(st_data_t);
typedef char st_check_for_sizeof_st_index_t[sizeof(void*) == (int)sizeof(st_index_t) ? 1 : -1];
struct st_hash_type {
    int (*compare)(... /*st_data_t, st_data_t*/); /* st_compare_func* */
    st_index_t (*hash)(... /*st_data_t*/);        /* st_hash_func* */
};

#define ST_INDEX_BITS (sizeof(st_index_t) * CHAR_BIT)
struct st_table {
    const struct st_hash_type *type;
    st_index_t num_bins;
    unsigned int entries_packed : 1;
    st_index_t num_entries : ST_INDEX_BITS - 1;
    union {
	struct {
	    struct st_table_entry **bins;
	    struct st_table_entry *head, *tail;
	} big;
	struct {
	    struct st_packed_entry *entries;
	    st_index_t real_entries;
	} packed;
    } as;
};

