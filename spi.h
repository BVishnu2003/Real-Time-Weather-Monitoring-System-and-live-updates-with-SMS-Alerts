#ifndef SPI_H
#define SPI_H

/* Initialize SPI0 */
void SPI_Init(void);

/* Transfer one byte through SPI */
unsigned char SPI_Write(unsigned char data);

/* MCP3204 Chip Select */
void SPI_CS_Low(void);
void SPI_CS_High(void);

#endif
