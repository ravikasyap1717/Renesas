/*
 * zelib-properties.h
 *
 * Created on: Jul 13, 2016
 *     Author: Mike McDonald @ KISStek.com
 */

#ifndef _ZELIB_PROPERTIES_H_
#define _ZELIB_PROPERTIES_H_

typedef enum {
    ZE_PROPERTY_TYPE_INT,
    ZE_PROPERTY_TYPE_UINT,
    ZE_PROPERTY_TYPE_SHORT,
    ZE_PROPERTY_TYPE_USHORT,
    ZE_PROPERTY_TYPE_DOUBLE,
    ZE_PROPERTY_TYPE_STRING,
    ZE_PROPERTY_TYPE_BYTE,
    ZE_PROPERTY_TYPE_UBYTE,
    ZE_PROPERTY_TYPE_NONE,
} ze_property_type_t;

typedef enum {
    ZE_PROPERTY_ACCESS_NONE,
    ZE_PROPERTY_ACCESS_READ_ONLY,
    ZE_PROPERTY_ACCESS_WRITE_ONLY,
    ZE_PROPERTY_ACCESS_READ_WRITE,
} ze_property_access_t;

typedef struct {
    char *name;
    ze_property_type_t type;
    unsigned int offset;
    unsigned int size;
    unsigned int count;
    ze_property_access_t access;
} ze_property_entry_t;


#define ZeOffsetOf(p_type,field) \
        ((Cardinal) (((char *) (&(((p_type)NULL)->field))) - ((char *) NULL)))

size_t ZE_Property_Size(ze_property_type_t t);

#endif /* _ZELIB_PROPERTIES_H_ */
