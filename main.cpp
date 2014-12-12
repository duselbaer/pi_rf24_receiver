#include "NRF24L01/v1/NRF24L01.hpp"
#include "NRF24L01/v1/driver/Raspberry.hpp"

#include <iostream>
#include <fstream>

int main(int, char**)
{
  // Instanciate the Raspberry Hardware using the "standard" ports
  typedef NRF24L01::driver::Raspberry<> NRF_HW;
  typedef NRF24L01::NRF24L01<NRF_HW>    NRF;

  NRF_HW nrf_hw;
  NRF    nrf(nrf_hw);
  nrf.init();

  nrf.setPayloadSize(0, 0);
  nrf.openReadingPipe(0, 0x0102030405);
  nrf.standBy();
  nrf.startListening();

  std::cout << "Device initialized" << std::endl;

  nrf.dumpStatus(std::cout);

  // return 0;
  while (1)
  {
    // disable debug output to be written to std::cout
    std::streambuf* cout_sbuf = std::cout.rdbuf();
    std::ofstream   fout("/dev/null");
    std::cout.rdbuf(fout.rdbuf());

    while (!nrf.available());

    // enable std::cout again
    std::cout.rdbuf(cout_sbuf);

    uint8_t buffer[32];
    buffer[0] = 0;

    nrf.read(buffer, 32);
    buffer[12] = 0;

    std::cout << "GOT: " << reinterpret_cast<const char*>(buffer) << std::endl;
  }
}
