
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
 * $Id$
 *
 * Description: Perfect switch, of course it is perfect and no latency or what
 *              so ever. Every cycle it is woke up and perform all the
 *              necessary routings that must be done. Note, this switch also
 *              has number of input ports/output ports and has a routing table
 *              as well.
 *
 */

#ifndef PerfectSwitch_H
#define PerfectSwitch_H

#include "mem/ruby/common/Global.hh"
#include "mem/gems_common/Vector.hh"
#include "mem/ruby/common/Consumer.hh"
#include "mem/ruby/system/NodeID.hh"

class MessageBuffer;
class NetDest;
class SimpleNetwork;

class LinkOrder {
public:
  int m_link;
  int m_value;
};

class PerfectSwitch : public Consumer {
public:
  // Constructors

  // constructor specifying the number of ports
  PerfectSwitch(SwitchID sid, SimpleNetwork* network_ptr);
  void addInPort(const Vector<MessageBuffer*>& in);
  void addOutPort(const Vector<MessageBuffer*>& out, const NetDest& routing_table_entry);
  void clearRoutingTables();
  void clearBuffers();
  void reconfigureOutPort(const NetDest& routing_table_entry);
  int getInLinks() const { return m_in.size(); }
  int getOutLinks() const { return m_out.size(); }

  // Destructor
  ~PerfectSwitch();

  // Public Methods
  void wakeup();

  void printStats(ostream& out) const;
  void clearStats();
  void printConfig(ostream& out) const;

  void print(ostream& out) const;
private:

  // Private copy constructor and assignment operator
  PerfectSwitch(const PerfectSwitch& obj);
  PerfectSwitch& operator=(const PerfectSwitch& obj);

  // Data Members (m_ prefix)
  SwitchID m_switch_id;

  // vector of queues from the components
  Vector<Vector<MessageBuffer*> > m_in;
  Vector<Vector<MessageBuffer*> > m_out;
  Vector<NetDest> m_routing_table;
  Vector<LinkOrder> m_link_order;
  int m_virtual_networks;
  int m_round_robin_start;
  int m_wakeups_wo_switch;
  SimpleNetwork* m_network_ptr;
};

// Output operator declaration
ostream& operator<<(ostream& out, const PerfectSwitch& obj);

// ******************* Definitions *******************

// Output operator definition
extern inline
ostream& operator<<(ostream& out, const PerfectSwitch& obj)
{
  obj.print(out);
  out << flush;
  return out;
}

#endif //PerfectSwitch_H