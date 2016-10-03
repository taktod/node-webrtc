#include "webrtc/api/mediaconstraintsinterface.h"
#include <string>

namespace node_webrtc {

class NodeConstraints : public webrtc::MediaConstraintsInterface {
public:
  NodeConstraints() {}
  virtual ~NodeConstraints() {}
  virtual const Constraints &GetMandatory() const {
    return _mandatory;
  }
  virtual const Constraints &GetOptional() const {
    return _optional;
  }
  template<class T>
  void AddMandatory(const std::string &key, const T &value) {
    _mandatory.push_back(Constraint(key, rtc::ToString<T>(value)));
  }

  template<class T>
  void SetMandatory(const std::string &key, const T &value) {
    std::string value_str;
    if(_mandatory.FindFirst(key, &value_str)) {
      for(Constraints::iterator iter = _mandatory.begin();iter != _mandatory.end(); ++iter) {
        if(iter->key == key) {
          _mandatory.erase(iter);
          break;
        }
      }
    }
    _mandatory.push_back(Constraint(key, rtc::ToString<T>(value)));
  }

  template<class T>
  void AddOptional(const std::string &key, const T &value) {
    _optional.push_back(Constraint(key, rtc::ToString<T>(value)));
  }
private:
  Constraints _mandatory;
  Constraints _optional;
}

}
