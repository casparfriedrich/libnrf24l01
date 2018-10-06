#include <cstdint>
#include <cstring>
#include <type_traits>

#include <nrf24l01/ispi.hpp>
#include <nrf24l01/rf24_ll.hpp>
#include <nrf24l01/types.hpp>

using namespace std;

static const uint8_t dummyByte = 0xFF;

template <typename TYPE>
static constexpr typename underlying_type<TYPE>::type asUnderlyingType(TYPE enumValue)
{
  return (static_cast<typename underlying_type<TYPE>::type>(enumValue));
}

RF24_LL::RF24_LL(ISpi& spi) : _spi(spi) {}

RF24_LL::~RF24_LL() {}

uint8_t RF24_LL::transmit(
    uint8_t command,
    const uint8_t txBytes[],
    uint8_t rxBytes[],
    uint8_t numBytes)
{
  uint8_t status;
  uint8_t buffer[numBytes + 1];

  if (txBytes != NULL)
  {
    memcpy(&buffer[1], txBytes, numBytes);
  }
  else
  {
    memset(&buffer[1], dummyByte, numBytes);
  }

  buffer[0] = command;

  _spi.transmit_receive(buffer, buffer, numBytes + 1);

  status = buffer[0];

  if (rxBytes != NULL)
  {
    memcpy(rxBytes, &buffer[1], numBytes);
  }

  return (status);
}

uint8_t RF24_LL::R_REGISTER(RF24_Register address, uint8_t bytes[], uint8_t numBytes)
{
  uint8_t command = asUnderlyingType(RF24_Command::R_REGISTER) | asUnderlyingType(address);
  uint8_t status = transmit(command, NULL, bytes, numBytes);

  return (status);
}

uint8_t RF24_LL::W_REGISTER(RF24_Register address, const uint8_t bytes[], uint8_t numBytes)
{
  uint8_t command = asUnderlyingType(RF24_Command::W_REGISTER) | asUnderlyingType(address);
  uint8_t status = transmit(command, bytes, NULL, numBytes);

  return (status);
}

uint8_t RF24_LL::R_RX_PAYLOAD(uint8_t bytes[], uint8_t numBytes)
{
  uint8_t command = asUnderlyingType(RF24_Command::R_RX_PAYLOAD);
  uint8_t status = transmit(command, NULL, bytes, numBytes);

  return (status);
}

uint8_t RF24_LL::W_TX_PAYLOAD(const uint8_t bytes[], uint8_t numBytes)
{
  uint8_t command = asUnderlyingType(RF24_Command::W_TX_PAYLOAD);
  uint8_t status = transmit(command, bytes, NULL, numBytes);

  return (status);
}

uint8_t RF24_LL::FLUSH_TX()
{
  uint8_t command = asUnderlyingType(RF24_Command::FLUSH_TX);
  uint8_t status = transmit(command, NULL, NULL, 0);

  return (status);
}

uint8_t RF24_LL::FLUSH_RX()
{
  uint8_t command = asUnderlyingType(RF24_Command::FLUSH_RX);
  uint8_t status = transmit(command, NULL, NULL, 0);

  return (status);
}

uint8_t RF24_LL::REUSE_TX_PL()
{
  uint8_t command = asUnderlyingType(RF24_Command::REUSE_TX_PL);
  uint8_t status = transmit(command, NULL, NULL, 0);

  return (status);
}

uint8_t RF24_LL::R_RX_PL_WID(uint8_t& payloadLength)
{
  uint8_t command = asUnderlyingType(RF24_Command::R_RX_PL_WID);
  uint8_t status = transmit(command, NULL, &payloadLength, 1);

  return (status);
}

uint8_t RF24_LL::W_ACK_PAYLOAD(uint8_t pipe, const uint8_t bytes[], uint8_t numBytes)
{
  uint8_t command = asUnderlyingType(RF24_Command::W_ACK_PAYLOAD) | pipe;
  uint8_t status = transmit(command, bytes, NULL, numBytes);

  return (status);
}

uint8_t RF24_LL::W_TX_PAYLOAD_NOACK(const uint8_t bytes[], uint8_t numBytes)
{
  uint8_t command = asUnderlyingType(RF24_Command::W_TX_PAYLOAD_NOACK);
  uint8_t status = transmit(command, bytes, NULL, numBytes);

  return (status);
}

uint8_t RF24_LL::NOP()
{
  uint8_t command = asUnderlyingType(RF24_Command::NOP);
  uint8_t status = transmit(command, NULL, NULL, 0);

  return (status);
}
