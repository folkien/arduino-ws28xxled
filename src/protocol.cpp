#include "protocol.h"
#include "Arduino.h"
#include <string.h>

/// function pointer
typedef void (*pFun)(const char *);


/// str names of commands
static const char * commands_str[] =
{
    "power off",
    "power on",
    "set color",
    "set colorall",
    "version",
};

/// protocol functions declaration
static void PowerOff(const char *);
static void PowerOn(const char *);
static void SetColor(const char *);
static void SetColorAll(const char *);
static void Version(const char *);

/// funs of commands
static pFun commands_funs[] =
{
    &PowerOff,
    &PowerOn,
    &SetColor,
    &SetColorAll,
    &Version,
};

void Protocol::Parse()
{
  /// for debug mode send again received data
  Serial.write(m_rxBuffer);
}

///
void Protocol::Receive(char c)
{
    if (m_rxPos < rxBufferSize)
    {
        m_rxBuffer[m_rxPos++] = c;
        /// if end line found then Parse
        if (c == '\n')
        {
            Parse();

            /// Clear Rx Buffer
            memset(m_rxBuffer,0,rxBufferSize);
            m_rxPos = 0;
        }
    }
}

/// protocol functions declaration
void PowerOff(const char *)
{

}
void PowerOn(const char *)
{

}
void SetColor(const char *)
{

}
void SetColorAll(const char *)
{

}
void Version(const char *)
{

}
