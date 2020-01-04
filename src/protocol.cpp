#include "protocol.h"
#include "Arduino.h"
#include <string.h>
#include "version.h"

/// macro of array sizeof
#define array_sizeof(arr)     (sizeof(arr) / sizeof((arr)[0]))

/// debug trace define
#define debug_trace Serial.write

/// function pointer
typedef void (*pFun)(const char *);


/// tx buffer size
constexpr static uint32_t txBufferSize = 64;
/// tx buffer
char txBuffer[txBufferSize];

/// str names of commands
static const char * commands_str[] =
{
    "power off",
    "power on",
    "set color",
    "set colorall",
    "help",
    "version",
};

/// protocol functions declaration
static void PowerOff(const char *);
static void PowerOn(const char *);
static void SetColor(const char *);
static void SetColorAll(const char *);
static void Help(const char *);
static void Version(const char *);

/// funs of commands
static pFun commands_funs[] =
{
    &PowerOff,
    &PowerOn,
    &SetColor,
    &SetColorAll,
    &Help,
    &Version,
};

bool Protocol::StartsWith(const char* str1, const char* str2)
{
	while (*str1 && *str2) {
		if (*str1 != *str2)
			return false;
		str1++;
		str2++;
	}

	if (*str2)
		return false;

	return true;
}

void Protocol::Parse()
{
  for (uint32_t i = 0; i< array_sizeof(commands_str);++i)
  {
      if (StartsWith(m_rxBuffer,commands_str[i]) == true)
      {
          commands_funs[i](m_rxBuffer+strlen(commands_str[i]));
          return ;
      }
  }

  /// in case of not founding command
  debug_trace("Command not known\n");
  debug_trace(m_rxBuffer);
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
void PowerOff(const char *ptr)
{

}

void PowerOn(const char *ptr)
{

}

void SetColor(const char *ptr)
{
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
    uint16_t position = 0;

    /// parse position
    sscanf(ptr,"%04u",&position);
    /// parse color
    sscanf(ptr,"%02x%02x%02x",&red, &green, &blue);

    sprintf(txBuffer,"SetColor to (%u,%u,%u) at %u.\n",red,green,blue,position);
    debug_trace(txBuffer);
}

void SetColorAll(const char *ptr)
{
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;

    /// parse color
    sscanf(ptr,"%02x%02x%02x",&red, &green, &blue);

    sprintf(txBuffer,"SetColorAll to (%u,%u,%u) at %u.\n",red,green,blue);
    debug_trace(txBuffer);
}

void Help(const char *ptr)
{
  for (uint32_t i = 0; i< array_sizeof(commands_str);++i)
  {
      debug_trace("Command '");
      debug_trace(commands_str[i]);
      debug_trace("'\n");
  }

}

void Version(const char *ptr)
{
  Serial.write(VERSION);
  Serial.write(AUTHOR);
}
