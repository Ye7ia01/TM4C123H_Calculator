#include "calc.h"

char* global_input;


int compute(char* input)
{
	
	int op1 , op2; // the two operands (overwritten for every existing operator) 
	op1 = get_operand(0,input);  // operator 1 is the first string before any mathematical operator
	int op_index = get_operator_index(0,input); // know where is the first mathimatical operator
  
	if (op_index == -1) // if no mathematical operator found
	{
		return atoi(input); // the string input entered will be returned as output
	}
  
	for(int i=op_index;i<strlen(input);i++) // loop on the input string 
    
	{
		while(op_index != -1) // while exist mathematical operators
                {
                  op2 = get_operand(op_index+1,input); // mathimatical operand is the string starting from operator index until next operator index
                  op1 = calc(op1,op2,input[op_index]); // operand 1 becomes the result of the previeus equation , then loop will continue for operand 2 and so on
                  op_index = get_operator_index(op_index+1,input); // updated operator index
                }
	}
	
	return op1; // operand 1 is the final result as it is the accumilated calculation of the string
}

int get_operand(int start,char* input)
{
	char operand[16] = {'\0'};
	int j=0;
	for (int i=start;i<=strlen(input);i++) // loop until current char is an operator
	{
  
		if (is_operator(input[i]) || input[i] == '\0') //if current char is operator return the previeus string ("operand") 
		{
		int op = atoi(operand);
		return op;
		}
		
		operand[j]=input[i]; // if not an operator put the char in "operand" string
		j++;
	}
        return 0;
}


int get_operator_index(int start,char* input)
{
	
	for (int i=start;i<strlen(input);i++)
	{
		if (is_operator(input[i])) { return i; }
	}
  
	return -1;
}

int calc(int x,int y,char c)
{
	 switch(c)
	{
		case '*' : return x*y; break;
		case '/' : return x/y; break;// no need to check for division by zero as it is already handled in "has_error" function
		case '+' : return x+y; break;
		case '-' : return x-y; break;
	}
        return 0;
}

bool is_operator(char x)
{
	return (x=='*' || x=='/' || x=='+' || x=='-');	
}

char* to_string(int x)
{
        /* type casting algorithm ( casts string to integer char by char by having modulus the char +48 ( to get ascii ) ) */
	int negative_flag = 0;
	int i=0;
	char result[16] = {'\0'};
	if (x < 0)
	{
		negative_flag = 1;
		x *= -1;
	}
  
	int mod = 10 ;
  
	while(x != 0 )
	{
		result[i]= (x %mod / (mod/10) ) + 48 ;
		i++;
		x = x - x%mod;
		mod *= 10 ; 
	}
	if (negative_flag == 1)
	{
		result[i] = '-';
	}
	return result ; 
}

char* get_final_result(char* input)
{
        if (has_error(input)) // check for errors first
        {
          return 0;
        }
	int x = compute(input); // get integer result for the equation
	return to_string(x); // return the string result after casting
}

int has_error(char* input) // error detector function which return (1) if equation has an eror or 0 if no errors detected
{
  
        if(strlen(input) == 0)  // if no equation was given
          return 1;
        
        for(int i=0;i<strlen(input);i++)
        {
          if (input[i] == '/' && input[i+1] == '0')  // if division by zero detected  
          {
            return 1;
          }
                  
          if ((input[i] == '*' || input[i] == '*') && (input[i+1] == '*' || input[i+1] == '/' )) // if (*) OR (/) followed by (*) OR (/)
          {
            return 1;
          }
          if ((input[i] == '+' || input[i] == '-') && (input[i+1] == '*' || input[i+1] == '/' )) // if (+) OR (-) followed by (*) OR (/)
          {
            return 1;
          }
          if ((input[i] == '*' || input[i] == '/') && (input[i+1] == '+' || input[i+1] == '-' )) // if (*) OR (/) followed by (+) OR (-)
          { 
            return 1;
          }
          
          if ((input[i] == '+') && (input[i+1] == '+'))  // if (+) followed by (+)
          {
            return 1;
          }
          
        }
         
        
        return 0;
}


