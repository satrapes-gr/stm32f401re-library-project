#ifndef UTILS_H
#define UTILS_H
#include "stm32f4xx.h"
#include "IO.h"

#include <stdbool.h>
#include <assert.h>

#include <stdio.h>

#define DISABLE_BITS_AND_CHECK_RETURN_ERROR(ADDRESS, BIT_MASK, ERROR, SUCCESS)\
                                            do {\
                                                bool result;\
                                                result = __clearBitMask((ADDRESS), (BIT_MASK));\
                                                if (result)\
                                                {\
                                                    return (ERROR);\
                                                } else\
                                                {\
                                                    return (SUCCESS);\
                                                }\
                                            }while(0)

#define ENABLE_BITS_AND_CHECK_RETURN_ERROR(ADDRESS, BIT_MASK, ERROR, SUCCESS)\
                                            do {\
                                                bool result;\
                                                result = __setBitMask((ADDRESS), (BIT_MASK));\
                                                if (result)\
                                                {\
                                                    return (ERROR);\
                                                } else\
                                                {\
                                                    return (SUCCESS);\
                                                }\
                                            } while(0)

/* Check if function result is equal to success. If not fail as early as possible */
#define CHECK_OUTPUT(RESULT, SUCCESS)\
                            do {\
                                if ((RESULT)!= (SUCCESS)) {\
                                    return (RESULT);\
                                }\
                            } while(0)
/**
 * @brief Set a bitmask in a register
 * @param reg_address Address of register that we want to set a bit on
 * @param bit_mask Bitmask that we want to set
 * @return bool 0 if set bit succeeded and 1 if it failed
 */
bool __setBitMask(ioAddress *reg_address, uint32_t bit_mask);

/**
 * @brief Clear given bit mask in a register
 * @param reg_address Address of register that we want to clear bits on
 * @param bit_mask Bitmask that we want to clear
 * @return bool 0 if clearing succeeded and 1 if it failed
 */
bool __clearBitMask(ioAddress *reg_address, uint32_t bit_mask);
#endif /* UTILS_H */
