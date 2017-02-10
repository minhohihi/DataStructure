//
//  DataStrucu_Misc.h
//  DataStructureCore
//
//  Created by Maverick on 2017. 2. 9..
//  Copyright © 2017년 Minhohihi. All rights reserved.
//

#include    <stdio.h>
#include    <stdlib.h>


#ifndef __DATASTRUCT_MISC_H__
#define __DATASTRUCT_MISC_H__

#define IN
#define OUT

#ifndef TRUE
    #define TRUE                                                    (1)
#endif

#ifndef FALSE
    #define FALSE                                                   (0)
#endif


#define SUCCESS                                                     (1)
#define FAIL                                                        (0)

#define FLOATFACTOR                                                 (12)
#define FLOATPRECISION                                              (1 << FLOATFACTOR)
#define FLOATMASK                                                   (FLOATPRECISION - 1)

#define PI                                                          ((float)(3.1415926535f))
#define LnE                                                         ((float)(2.718f))


#define GET_MIN(a,b)                                                (((a)<(b)) ? (a) : (b))
#define GET_MAX(a,b)                                                (((a)<(b)) ? (b) : (a))
#define CLIP3(nMin, nMax, x)                                        ((x > nMax) ? nMax : (x < nMin ? nMin : x))
#define SQRT(a)                                                     sqrt(a)
#define POW(x, y)                                                   pow(x, y)
#define EXP(x)                                                      exp((x))
#define EXP_F(x)                                                    expf((x))
#define ABSM(A)                                                     abs(A)          //((A)<(0) ? (-(A)):(A)) //!< abs macro, faster than procedure
#define ABSM_F(A)                                                   fabsf(A)        //((A)<(0) ? (-(A)):(A)) //!< abs macro, faster than procedure
#define ABSM_D(A)                                                   fabs(A)         //((A)<(0) ? (-(A)):(A)) //!< abs macro, faster than procedure
#define ROUND(x)                                                    (INT32)((F32)(x) + 0.5f)


#define STRCPY(extension, address)                                  strcpy(extension, address)
#define STRCMP(address, extension)                                  strcmp(address, extension)


#define FFLUSH(fp)                                                  fflush(fp)
#define FSEEK(fp, var, position)                                    fseek(fp, var, position)
#define FTELL(fp)                                                   ftell(fp)
#define FOPEN(filename, mode)                                       fopen(filename, mode)
#define FCLOSE(fp)                                                  fclose(fp)
#ifndef FREAD
    #define FREAD(buffer, sizeoftype, sizeofdata, filepoint)        fread(buffer, sizeoftype, sizeofdata, filepoint)
#endif
#ifndef FWRITE
    #define FWRITE(buffer, sizeoftype, sizeofdata, filepointer)     fwrite(buffer, sizeoftype, sizeofdata, filepointer)
#endif


#define MEMCPY(dst, src, length)                                    memcpy((dst), (src), (length))
#define MEMSET(dst, var, length)                                    memset((dst), (var), (length))


#define MALLOC(size)                                                malloc(size)


#define ADDRESS_STORAGE_SIZE                                        sizeof(size_t)
#define ALIGN_ADDRESS(addr, align)                                  (void*)(((size_t)(addr) + ((align) - 1)) & (size_t)-(align))


#define MAKE_STRIDE(nWidth)                                         ((((nWidth) + (2 * PADDING_SIZE)) + (PADDING_SIZE - 1)) & ~(PADDING_SIZE - 1))
#define GET_ALIGNED_LENGTH(value, align)                            ((value + (align - 1)) & ~(align - 1))
#define ROUND_BASE(x, base)                                         (x - (x & (base - 1)))


#if (defined(__GNUC__) && __GNUC__) || defined(__SUNPRO_C)
    #define MEM_ALIGNED(n)                                          __attribute__ ((aligned(n)))
#elif defined(_MSC_VER)
    #define MEM_ALIGNED(n)
#else
    #define MEM_ALIGNED(n)
#endif


#if (!defined (__INLINE)) && (!defined (__FORCE_INLINE))
    #if (defined (__GNUC__)) && (!defined (__GNUC_STDC_INLINE__))
        #define __FORCE_INLINE                                      __attribute__((always_inline))
        #define __INLINE                                            static inline
    #elif defined(_MSC_VER)
        #define __FORCE_INLINE                                      __forceinline
        #define __INLINE                                            __inline
    #else
        #define __FORCE_INLINE                                      static inline __attribute__((always_inline))
        #define __INLINE                                            static inline
    #endif
#endif


#define GET_INTEGRAL_PIX_POS(pIntegralSrc, x, y, nStride)           (&(pIntegralSrc[(y) * nStride + (x)]))
#define CALCULATE_INTEGRAL_SUM(nIntTable, nOffset)                  (nIntTable.pBR[nOffset] + nIntTable.pTL[nOffset] - nIntTable.pTR[nOffset] - nIntTable.pBL[nOffset])

#define SET_UNUSED_VARIABLE(variable)                               (void)variable


#define BILINEAR_APPX(nVal0, nVal1, nRatio, nPrecision)             (((nVal0 * nRatio) + (nVal1 * ((1 << nPrecision) - nRatio))) >> nPrecision)


#define CHECK_POINTER_VALIDATION(pointer, retval)\
                                                                    if(NULL == pointer)\
                                                                        return retval;

#define CHECK_PARAM_VALIDATION(condition, retval)\
                                                                    if(0 == condition)\
                                                                        return retval;

#define SAFEALLOC(pHandle, size, align, type)\
                                                                    if(NULL == pHandle)\
                                                                    {\
                                                                        void    *pAlignedHandle = NULL;\
                                                                        void    *pTmpHandle = (void *)MALLOC((size + align - 1 + ADDRESS_STORAGE_SIZE) * sizeof(type));\
                                                                        if(NULL != pTmpHandle)\
                                                                        {\
                                                                            MEMSET(pTmpHandle, 0, ((size + align - 1 + ADDRESS_STORAGE_SIZE) * sizeof(type)));\
                                                                            pAlignedHandle = ALIGN_ADDRESS((unsigned char *)pTmpHandle + ADDRESS_STORAGE_SIZE, (int)align);\
                                                                            ((size_t *)pAlignedHandle)[-1] = (size_t)pTmpHandle;\
                                                                            pHandle = pAlignedHandle;\
                                                                        }\
                                                                        else\
                                                                            pHandle = NULL;\
                                                                    }


#define SAFEFREE(pHandle)\
                                                                    if(NULL != pHandle)\
                                                                    {\
                                                                        void    *pRealHandle = (void *)(((size_t *)pHandle)[-1]);\
                                                                        free(pRealHandle);\
                                                                        pHandle = NULL;\
                                                                    }

#endif
