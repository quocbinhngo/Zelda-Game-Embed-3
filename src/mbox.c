// -----------------------------------mbox.c -------------------------------------
#include "mbox.h"
#include "gpio.h"
#include "uart.h"
#include "stdarg.h"

/* Mailbox Data Buffer (each element is 32-bit)*/
/*
 * The keyword attribute allows you to specify special attributes
 *
 * The aligned(N) attribute aligns the current data item on an address
 * which is a multiple of N, by inserting padding bytes before the data item
 *
 * __attribute__((aligned(16)) : allocate the variable on a 16-byte boundary.
 * *
 * We must ensure that our our buffer is located at a 16 byte aligned address,
 * so only the high 28 bits contain the address
 * (last 4 bits is ZERO due to 16 byte alignment)
 *
 */
volatile unsigned int __attribute__((aligned(16))) mBuf[36];

/**
 * Read from the mailbox
 */
uint32_t mailbox_read(unsigned char channel)
{
    // Receiving message is buffer_addr & channel number
    uint32_t res;
    // Make sure that the message is from the right channel
    do
    {
        // Make sure there is mail to receive
        do
        {
            asm volatile("nop");
        } while (MBOX0_STATUS & MBOX_EMPTY);
        // Get the message
        res = MBOX0_READ;
    } while ((res & 0xF) != channel);

    return res;
}

/**
 * Write to the mailbox
 */
void mailbox_send(uint32_t msg, unsigned char channel)
{
    // Sending message is buffer_addr & channel number
    //  Make sure you can send mail
    do
    {
        asm volatile("nop");
    } while (MBOX1_STATUS & MBOX_FULL);
    // send the message
    MBOX1_WRITE = msg;
}

/**
 * Make a mailbox call. Returns 0 on failure, non-zero on success
 */
int mbox_call(unsigned int buffer_addr, unsigned char channel)
{
    // Check Buffer Address
    // Prepare Data (address of Message Buffer)
    unsigned int msg = (buffer_addr & ~0xF) | (channel & 0xF);
    mailbox_send(msg, channel);

    /* now wait for the response */
    /* is it a response to our message (same address)? */
    if (msg == mailbox_read(channel))
    {
        /* is it a valid successful response (Response Code) ? */

        return (mBuf[1] == MBOX_RESPONSE);
    }

    return 0;
}

/*
 * Function for setup mbox
 */
void mbox_buffer_setup(unsigned int buffer_addr, unsigned int tag_identifier,
                       unsigned int req_length, ...)
{

    volatile unsigned int *mb = (unsigned int *)((unsigned long)buffer_addr); // create the mailbox buffer array for request

    const int DEFAULT_NUM_BUFFER_ELEMENTS = 6;                 // The default number of buffer elements
    int buffer_num = DEFAULT_NUM_BUFFER_ELEMENTS + req_length; // The number length of the buffer request

    mb[0] = buffer_num * 4; // Message Buffer Size in bytes (`buffer_num` elements * 4 bytes each)
    mb[1] = MBOX_REQUEST;   // Message Request Code (this is a request message)

    mb[2] = tag_identifier; // Assign TAG Identifier
    mb[3] = 8;              // // Value buffer size in bytes (max of request and response lengths) (The max length of all values is 8)
    mb[4] = 0;              // REQUEST CODE: 0

    va_list arg_ptr;                     // Init the variable arguments
    va_start(arg_ptr, req_length);       // Start to read
    for (int i = 0; i < req_length; i++) // set data based on variable args
    {
        mb[5 + i] = va_arg(arg_ptr, unsigned int);
    }
    mb[5 + req_length] = 0; // clear output buffer
    va_end(arg_ptr);        // End to read variable arguments

    mb[5 + req_length + 1] = MBOX_TAG_LAST; // Assign the mbox tag last

    if (mbox_call(buffer_addr, MBOX_CH_PROP)) // If calling the request is success
    {
    }
    else // If calling the request is failed
    {
        uart_puts("Unable to query!\n");
    }
}