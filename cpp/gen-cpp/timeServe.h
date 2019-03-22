/**
 * Autogenerated by Thrift Compiler (0.12.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef timeServe_H
#define timeServe_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include "timeRPC_types.h"



#ifdef _MSC_VER
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class timeServeIf {
 public:
  virtual ~timeServeIf() {}
  virtual int32_t getCurrtentTime() = 0;
};

class timeServeIfFactory {
 public:
  typedef timeServeIf Handler;

  virtual ~timeServeIfFactory() {}

  virtual timeServeIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(timeServeIf* /* handler */) = 0;
};

class timeServeIfSingletonFactory : virtual public timeServeIfFactory {
 public:
  timeServeIfSingletonFactory(const ::apache::thrift::stdcxx::shared_ptr<timeServeIf>& iface) : iface_(iface) {}
  virtual ~timeServeIfSingletonFactory() {}

  virtual timeServeIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(timeServeIf* /* handler */) {}

 protected:
  ::apache::thrift::stdcxx::shared_ptr<timeServeIf> iface_;
};

class timeServeNull : virtual public timeServeIf {
 public:
  virtual ~timeServeNull() {}
  int32_t getCurrtentTime() {
    int32_t _return = 0;
    return _return;
  }
};


class timeServe_getCurrtentTime_args {
 public:

  timeServe_getCurrtentTime_args(const timeServe_getCurrtentTime_args&);
  timeServe_getCurrtentTime_args& operator=(const timeServe_getCurrtentTime_args&);
  timeServe_getCurrtentTime_args() {
  }

  virtual ~timeServe_getCurrtentTime_args() throw();

  bool operator == (const timeServe_getCurrtentTime_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const timeServe_getCurrtentTime_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const timeServe_getCurrtentTime_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class timeServe_getCurrtentTime_pargs {
 public:


  virtual ~timeServe_getCurrtentTime_pargs() throw();

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _timeServe_getCurrtentTime_result__isset {
  _timeServe_getCurrtentTime_result__isset() : success(false) {}
  bool success :1;
} _timeServe_getCurrtentTime_result__isset;

class timeServe_getCurrtentTime_result {
 public:

  timeServe_getCurrtentTime_result(const timeServe_getCurrtentTime_result&);
  timeServe_getCurrtentTime_result& operator=(const timeServe_getCurrtentTime_result&);
  timeServe_getCurrtentTime_result() : success(0) {
  }

  virtual ~timeServe_getCurrtentTime_result() throw();
  int32_t success;

  _timeServe_getCurrtentTime_result__isset __isset;

  void __set_success(const int32_t val);

  bool operator == (const timeServe_getCurrtentTime_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const timeServe_getCurrtentTime_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const timeServe_getCurrtentTime_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _timeServe_getCurrtentTime_presult__isset {
  _timeServe_getCurrtentTime_presult__isset() : success(false) {}
  bool success :1;
} _timeServe_getCurrtentTime_presult__isset;

class timeServe_getCurrtentTime_presult {
 public:


  virtual ~timeServe_getCurrtentTime_presult() throw();
  int32_t* success;

  _timeServe_getCurrtentTime_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class timeServeClient : virtual public timeServeIf {
 public:
  timeServeClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  timeServeClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  int32_t getCurrtentTime();
  void send_getCurrtentTime();
  int32_t recv_getCurrtentTime();
 protected:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class timeServeProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  ::apache::thrift::stdcxx::shared_ptr<timeServeIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (timeServeProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_getCurrtentTime(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  timeServeProcessor(::apache::thrift::stdcxx::shared_ptr<timeServeIf> iface) :
    iface_(iface) {
    processMap_["getCurrtentTime"] = &timeServeProcessor::process_getCurrtentTime;
  }

  virtual ~timeServeProcessor() {}
};

class timeServeProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  timeServeProcessorFactory(const ::apache::thrift::stdcxx::shared_ptr< timeServeIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::apache::thrift::stdcxx::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::apache::thrift::stdcxx::shared_ptr< timeServeIfFactory > handlerFactory_;
};

class timeServeMultiface : virtual public timeServeIf {
 public:
  timeServeMultiface(std::vector<apache::thrift::stdcxx::shared_ptr<timeServeIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~timeServeMultiface() {}
 protected:
  std::vector<apache::thrift::stdcxx::shared_ptr<timeServeIf> > ifaces_;
  timeServeMultiface() {}
  void add(::apache::thrift::stdcxx::shared_ptr<timeServeIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  int32_t getCurrtentTime() {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->getCurrtentTime();
    }
    return ifaces_[i]->getCurrtentTime();
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class timeServeConcurrentClient : virtual public timeServeIf {
 public:
  timeServeConcurrentClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  timeServeConcurrentClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  int32_t getCurrtentTime();
  int32_t send_getCurrtentTime();
  int32_t recv_getCurrtentTime(const int32_t seqid);
 protected:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
  ::apache::thrift::async::TConcurrentClientSyncInfo sync_;
};

#ifdef _MSC_VER
  #pragma warning( pop )
#endif



#endif