#include <stdint.h>

class Protocol
{
    public:
        Protocol() {}
        ~Protocol() {}

        ///
        void Receive(char c);

    private:
        /// rx buffer size
        constexpr static uint32_t rxBufferSize = 256;
        /// rx buffer
        char m_rxBuffer[rxBufferSize];
        /// rx buffer position
        uint32_t m_rxPos = 0;

        /// Parse rx buffer
        void Parse();
        ///
        bool StartsWith(const char* str1, const char* str2);
};

