#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__


int compute(char*); // takes keypad input as a string and returns the result as integer
int get_operand(int,char*); // detects & return operands of mathematical equation (used inside "compute")
int get_operator_index(int,char*); // return the index of mathematical operators (used inside "compute")
int calc(int,int,char); // takes the two operands returned by "get_operand" & the operator between them & returns the result (used inside compute)
bool is_operator(char); // 
char* to_string(int); // casts integer result to string to be printed on LCD 
char* get_final_result(char*); // calls "compute" for keypad input , then calls "to_string" to return answer as string
int has_error(char*); // checks for errors before "compute" (used in "get_final_result")

#endif
