#include "protocol.h"
#include "Arduino.h"
#include <string.h>

void Protocol::Parse()
{
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
