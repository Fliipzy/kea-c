#ifndef __SLOTMACHINE_H__
#define __SLOTMACHINE_H__

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_WHEELS 3
#define MAX_SYMBOLS 20
#define STD_USD_CRED_CNV 5

/*
This enum represents each symbol available in the wheels.
*/
typedef enum symbol
{
    APPLE,
    BAR,
    BELL,
    CHERRY,
    PEAR,
    LEMON,
    ORANGE,
    GRAPES
} symbol_t;

/*
Represents the various settings in the slotmachine:
US dollars to credit conversion, price per spin etc.
*/
typedef struct slotmachine_config
{
    unsigned char spin_credit_price;
    unsigned char usd_to_credit_conversion;
} slotmachine_config_t;

/*
This struct represents the wheel in the slotmachine.
A wheel holds an array of 10 symbols & an integer
that tells which symbol is the current one.
*/
typedef struct wheel
{
    unsigned char current_symbol;
    symbol_t symbols[MAX_SYMBOLS];
} wheel_t;

/*
This struct represents the rules of the slotmachine i.e 
which order of symbols - when rolled - pays back.
*/
typedef struct rule 
{
    symbol_t symbols[MAX_WHEELS];
    unsigned short price;
} rule_t;

/*
This struct represents the slotmachine.
It holds a maximum of 3 wheel pointers.
*/
typedef struct slotmachine
{   
    wheel_t *wheels[MAX_WHEELS];
    slotmachine_config_t config;
    unsigned char rules_size;
    //Flexible array member feature with C99
    rule_t rules[]; 
} slotmachine_t;

/*
The create functions for the slotmachine structures. 
These functions all allocate memory, for each struct,
then initializes them with given arguments and returns
the pointer.
*/
slotmachine_t *create_slotmachine (slotmachine_config_t config, wheel_t *wheels[], rule_t rules[], unsigned char rules_size);
slotmachine_config_t create_slotmachine_config (unsigned char spin_credit_price, unsigned char usd_credit_conversion);
wheel_t *create_wheel (symbol_t symbols[]);
rule_t create_rule (symbol_t symbols[], unsigned short price);

/*
Creates a slotmachine struct with hardcoded values specific to the
assignment requirements. See README for more information.
*/
slotmachine_t* create_default_slotmachine();

/*
Function which deallocates the allocated memory for the slotmachine.
That also means every struct that slotmachine has a pointer to.
*/
void destroy_slotmachine(slotmachine_t *slotmachine);

/*
Spins the wheel given from argument.
Spin meaning picking a random symbol
from that wheels symbols array.

@param wheel: the wheel to spin.
*/
void spin_wheel(wheel_t *wheel);

/*
Returns the string value (name) of the symbol.

@param symbol: the symbol to get the name from.
*/
char *get_symbol_name(symbol_t symbol);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // __SLOTMACHINE_H__
