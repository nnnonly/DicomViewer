/*
 *
 *  Copyright (C) 1998-2019, OFFIS e.V.
 *  All rights reserved.  See COPYRIGHT file for details.
 *
 *  This software and supporting documentation were developed by
 *
 *    OFFIS e.V.
 *    R&D Division Health
 *    Escherweg 2
 *    D-26121 Oldenburg, Germany
 *
 *
 *  Module: dcmsign
 *
 *  Author: Marco Eichelberg
 *
 *  Purpose:
 *    classes: SiMD5
 *
 */

#ifndef SIMD5_H
#define SIMD5_H

#include "dcmtk/config/osconfig.h"

#ifdef WITH_OPENSSL

#include "dcmtk/dcmsign/simac.h"
#include "dcmtk/dcmsign/sitypes.h"

struct MD5state_st;
typedef struct MD5state_st MD5_CTX;

/**
 * a class implementing the hash function MD5
 * @remark this class is only available if DCMTK is compiled with
 * OpenSSL support enabled.
 */
class DCMTK_DCMSIGN_EXPORT SiMD5 : public SiMAC
{
public:
  /// default constructor
  SiMD5();

  /// destructor
  virtual ~SiMD5();

  /** initializes the MAC algorithm.
   *  @return status code
   */
  virtual OFCondition initialize();

  /** feeds data into the MAC algorithm
   *  @param data pointer to raw data to be fed into the MAC, must not be NULL
   *  @param length number of bytes in raw data array
   *  @return status code
   */
  virtual OFCondition digest(const unsigned char *data, unsigned long length);

  /** finalizes the MAC and writes it to the given output array,
   *  which must be at least getSize() bytes large.
   *  After a call to finalize, the MAC algorithm must be initialized
   *  again, see initialize().
   *  @param result pointer to array of getSize() bytes into which the MAC is written
   *  @return status code
   */
  virtual OFCondition finalize(unsigned char *result);

  /** returns the size of a MAC in bytes.
   *  @return block size for this MAC algorithm
   */
  virtual unsigned long getSize() const;

  /** returns the type of MAC algorithm computed by this object
   *  @return type of MAC algorithm
   */
  virtual E_MACType macType() const;

  /** returns the DICOM identifier for this MAC algorithm
   *  @return DICOM defined term for algorithm
   */
  virtual const char *getDefinedTerm() const;

private:

  /// private undefined copy constructor
  SiMD5(SiMD5& arg);

  /// private undefined copy assignment operator
  SiMD5& operator=(SiMD5& arg);

  /// OpenSSL MD5 context
  MD5_CTX *ctx;
};

#endif
#endif
