#ifndef I2C_H
#define I2C_H
#include <avr/io.h>
#include "timer.h"

// MPU6050 address and registers
// Arduino will communicate through these register
#define MPU6050_ADDR 0x68 // MPU address to communicate via  I2C (AD0 is set to LOW)
#define PWR_MGMT_1 0x6B   // MPU power management address via  I2C
#define ACCEL_XOUT_H 0x3B // MPU x-axis output first 8 bits via  I2C
#define ACCEL_XOUT_L 0x3C // MPU x-axis output last 8 bits via  I2C
#define ACCEL_YOUT_H 0x3D // MPU y-axis output first 8 bits via  I2C
#define ACCEL_YOUT_L 0x3E // MPU y-axis output last 8 bits via  I2C
#define ACCEL_ZOUT_H 0x3F // MPU z-axis output first 8 bits via  I2C
#define ACCEL_ZOUT_L 0x40 // MPU z-axis output last 8 bits via  I2C
#define ACCEL_CONF 0x1C   // MPU acceleration configuration via I2C

// I2C functions
void initI2C();
void StartI2C_Trans(unsigned char SLA);
void StopI2C_Trans();
void Write(unsigned char data);
void Read_from(unsigned char SLA, unsigned char MEMADDRESS);
unsigned char Read_data();
void initAccel();

// Status code for I2C (to ensure it works)
#define I2C_START 0x08
#define I2C_REP_START 0x10
#define I2C_ARB_LOST 0x38
// Master Transmitter Mode Status Codes
#define I2C_MT_SLA_ACK 0x18
#define I2C_MT_SLA_NACK 0x20
#define I2C_MT_DATA_ACK 0x28
#define I2C_MT_DATA_NACK 0x30
// Master Receiver Mode Status Codes
#define I2C_MR_SLA_ACK 0x40
#define I2C_MR_SLA_NACK 0x48
#define I2C_MR_DATA_ACK 0x50
#define I2C_MR_DATA_NACK 0x58
// Slave Transmitter Mode Status Codes (Not implemented in this master-only library)
#define I2C_ST_SLA_ACK 0xA8
#define I2C_ST_ARB_LOST_SLA_ACK 0xB0
#define I2C_ST_DATA_ACK 0xB8
#define I2C_ST_DATA_NACK 0xC0
#define I2C_ST_LAST_DATA_ACK 0xC8
// Slave Receiver Mode Status Codes (Not implemented in this master-only library)
#define I2C_SR_SLA_ACK 0x60
#define I2C_SR_ARB_LOST_SLA_ACK 0x68
#define I2C_SR_GCALL_ACK 0x70
#define I2C_SR_ARB_LOST_GCALL_ACK 0x78
#define I2C_SR_DATA_ACK 0x80
#define I2C_SR_DATA_NACK 0x88
#define I2C_SR_GCALL_DATA_ACK 0x90
#define I2C_SR_GCALL_DATA_NACK 0x98
#define I2C_SR_STOP_REP_START 0xA0
// Miscellaneous Status Codes
#define I2C_BUS_ERROR 0x00
#define I2C_NO_INFO 0xF8
#endif