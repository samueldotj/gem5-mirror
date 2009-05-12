
/*
 * Copyright (c) 1999-2008 Mark D. Hill and David A. Wood
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * NetworkMessage.h
 *
 * Description:
 *
 * $Id$
 *
 */

#ifndef NetworkMessage_H
#define NetworkMessage_H

#include "mem/ruby/common/Global.hh"
#include "mem/gems_common/RefCnt.hh"
#include "mem/gems_common/RefCountable.hh"
#include "mem/ruby/slicc_interface/Message.hh"
#include "mem/protocol/MessageSizeType.hh"
#include "mem/ruby/common/NetDest.hh"

class Address;

class NetworkMessage;
typedef RefCnt<NetworkMessage> NetMsgPtr;

class NetworkMessage : public Message {
public:
  // Constructors
  NetworkMessage()
    :Message()
    {
      m_internal_dest_valid = false;
    }

  // Destructor
  virtual ~NetworkMessage() { }

  // Public Methods

  virtual const NetDest& getDestination() const = 0;
  virtual NetDest& getDestination() = 0;
  virtual const MessageSizeType& getMessageSize() const = 0;
  virtual MessageSizeType& getMessageSize() = 0;
  //  virtual const Address& getAddress() const = 0;
  //  virtual Address& getAddress() = 0;

  const NetDest& getInternalDestination() const {
    if (m_internal_dest_valid == false) {
      return getDestination();
    } else {
      return m_internal_dest;
    }
  }

  NetDest& getInternalDestination() {
    if (m_internal_dest_valid == false) {
      m_internal_dest = getDestination();
      m_internal_dest_valid = true;
    }
    return m_internal_dest;
  }

  virtual void print(ostream& out) const = 0;

private:
  // Private Methods

  // Data Members (m_ prefix)
  NetDest m_internal_dest;
  bool m_internal_dest_valid;
};

// Output operator declaration
ostream& operator<<(ostream& out, const NetworkMessage& obj);

// ******************* Definitions *******************

// Output operator definition
extern inline
ostream& operator<<(ostream& out, const NetworkMessage& obj)
{
  obj.print(out);
  out << flush;
  return out;
}

#endif //NetworkMessage_H