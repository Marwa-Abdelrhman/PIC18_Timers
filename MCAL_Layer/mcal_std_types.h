/* 
 * File:   mcal_std_types.h
 * Author: Marwa Abdelrahman
 *
 * Created on August 1, 2024, 12:56 AM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

#include"compilers.h"
#include"std_libraries.h"

/*.....................................Includes.....................................*/





/*.....................................Data Types Declarations.....................................*/
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef signed char sint8;
typedef signed short sint16;
typedef signed int sint32;
typedef uint8 Std_RetrunType;
/*.....................................Macros Declarations.....................................*/

#define STD_HIGH      0x01
#define STD_LOW       0x00
#define STD_ON        0x01
#define STD_OFF       0x00
#define STD_ACTIVE    0x01
#define STD_IDLE      0x00
#define E_OK          ((Std_RetrunType) 0x01)
#define E_NOK         ((Std_RetrunType) 0x00)
#define ZERO          0

/*.....................................Macros Functions Declarations.....................................*/

/*.....................................Functions Declarations.....................................*/
#endif	/* MCAL_STD_TYPES_H */

