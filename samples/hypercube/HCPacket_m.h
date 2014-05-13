//
// Generated file, do not edit! Created by opp_msgc 4.4 from HCPacket.msg.
//

#ifndef _HCPACKET_M_H_
#define _HCPACKET_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0404
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif



/**
 * Class generated from <tt>HCPacket.msg</tt> by opp_msgc.
 * <pre>
 * packet HCPacket
 * {
 *     int srcAddress;
 *     int destAddress;
 *     int hops = 0;
 * };
 * </pre>
 */
class HCPacket : public ::cPacket
{
  protected:
    int srcAddress_var;
    int destAddress_var;
    int hops_var;

  private:
    void copy(const HCPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const HCPacket&);

  public:
    HCPacket(const char *name=NULL, int kind=0);
    HCPacket(const HCPacket& other);
    virtual ~HCPacket();
    HCPacket& operator=(const HCPacket& other);
    virtual HCPacket *dup() const {return new HCPacket(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getSrcAddress() const;
    virtual void setSrcAddress(int srcAddress);
    virtual int getDestAddress() const;
    virtual void setDestAddress(int destAddress);
    virtual int getHops() const;
    virtual void setHops(int hops);
};

inline void doPacking(cCommBuffer *b, HCPacket& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, HCPacket& obj) {obj.parsimUnpack(b);}


#endif // _HCPACKET_M_H_
