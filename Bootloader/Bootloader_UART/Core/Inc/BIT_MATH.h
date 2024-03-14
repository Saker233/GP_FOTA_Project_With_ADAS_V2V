#ifndef _BIT_MATH_H
#define _BIT_MATH_H

#define SET_BIT(REG,BIT_NUMBER) 			(REG |=(1<<BIT_NUMBER))
#define CLR_BIT(REG,BIT_NUMBER) 			(REG &=~(1<<BIT_NUMBER))
#define TOGGLE_BIT(REG,BIT_NUMBER) 			(REG ^=(1<<BIT_NUMBER))
#define GET_BIT(REG,BIT_NUMBER) 			((REG>>BIT_NUMBER)&1)
#define WRITE_REG(REG, VAL)   				((REG) = (VAL))



#endif
