#ifndef __ACTIONS_H__
#define __ACTIONS_H__

#include "cocos2d.h"
#include "cocostudio/TriggerBase.h"


class  PlayMusic: public cocostudio::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     PlayMusic(void);
     virtual ~PlayMusic(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
	 int  _tag;
	 std::string _comName;
	 int  _type;
};

class  TMoveTo: public cocostudio::BaseTriggerAction
{
	DECLARE_CLASS_INFO
public:
	TMoveTo(void);
	virtual ~TMoveTo(void);

	virtual bool init();
	virtual void done();
	virtual void serialize(const rapidjson::Value &val);
	virtual void removeAll();
private:
	int  _tag;
	float _duration;
	cocos2d::Point _pos;
};


class TMoveBy : public cocostudio::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     TMoveBy(void);
     virtual ~TMoveBy(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
	int  _tag;
	float _duration;
	cocos2d::Point _pos;
	bool _reverse;
    bool _repeatForever;
};


class TRotateTo : public cocostudio::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     TRotateTo(void);
     virtual ~TRotateTo(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
	int  _tag;
	float _duration;
	float _deltaAngle;
};


class TRotateBy : public cocostudio::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     TRotateBy(void);
     virtual ~TRotateBy(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
	int  _tag;
	float _duration;
	float _deltaAngle;
	bool _reverse;
    bool _repeatForever;
};


class TScaleTo : public cocostudio::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     TScaleTo(void);
     virtual ~TScaleTo(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
	int  _tag;
	float _duration;
	cocos2d::Point _scale;
};


class TScaleBy : public cocostudio::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     TScaleBy(void);
     virtual ~TScaleBy(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
	int  _tag;
	float _duration;
	cocos2d::Point _scale;
	bool _reverse;
    bool _repeatForever;
};


class TSkewTo : public cocostudio::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     TSkewTo(void);
     virtual ~TSkewTo(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
	int  _tag;
	float _duration;
	cocos2d::Point _skew;
};


class TSkewBy : public cocostudio::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     TSkewBy(void);
     virtual ~TSkewBy(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
	int  _tag;
	float _duration;
	cocos2d::Point _skew;
	bool _reverse;
    bool _repeatForever;
};


class TriggerState : public cocostudio::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     TriggerState(void);
     virtual ~TriggerState(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
	int  _id;
	int _state;
};

class ArmaturePlayAction : public cocostudio::BaseTriggerAction
{
	DECLARE_CLASS_INFO
public:
	ArmaturePlayAction(void);
	virtual ~ArmaturePlayAction(void);

	virtual bool init();
	virtual void done();
	virtual void serialize(const rapidjson::Value &val);
	virtual void removeAll();
private:
	int _tag;
	std::string _comName;
	std::string _aniname;
};


class SequenceMoveTo : public cocostudio::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     SequenceMoveTo(void);
     virtual ~SequenceMoveTo(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
    int _tag;
    cocos2d::Point _endPos;
    float  _endDur;
    cocos2d::Point _startPos;
    float  _startDur;
    bool _repeatForever;
    float  _delayTime;
};


class JumpAction : public cocostudio::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     JumpAction(void);
     virtual ~JumpAction(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
    int   _tag;
    float _riseHeight;
    float _riseTime;
    float _jumpDelayTime;
    float _rotationTo;
};


class FallAction : public cocostudio::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     FallAction(void);
     virtual ~FallAction(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
    int   _tag;
    float _fallSpeed;
    float _rotationTo;
    float _fallTo;
};


class ChangeDoubleAttribute : public cocostudio::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     ChangeDoubleAttribute(void);
     virtual ~ChangeDoubleAttribute(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
    int   _tag;
    std::string _key;
    float _value;
    int _type;
    int _limit;
};


class AddAccToPositionY : public cocostudio::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     AddAccToPositionY(void);
     virtual ~AddAccToPositionY(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
    int   _tag;
    std::string _comName;
    std::string _key;
    float _acceleration;
};


class SequenceMoveToAndChangePositionY : public cocostudio::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     SequenceMoveToAndChangePositionY(void);
     virtual ~SequenceMoveToAndChangePositionY(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
    int getRandNum(int min, int max);
    void actionOver(cocos2d::Node* pSender, void* data);
private:
    int _tag;
    cocos2d::CCPoint _endPos;
    float  _endDur;
    cocos2d::CCPoint _startPos;
    float  _startDur;
    float  _delayTime;
    int    _maxPositionY;
    int    _minPositionY;
};


class SetNodeVisible : public cocostudio::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     SetNodeVisible(void);
     virtual ~SetNodeVisible(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
    int _tag;
    bool _show;
};


class PlayUIAnimation : public cocostudio::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     PlayUIAnimation(void);
     virtual ~PlayUIAnimation(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
    std::string _uiJsonName;
    std::string _animaitionName;
};


class StopAllActions : public cocostudio::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     StopAllActions(void);
     virtual ~StopAllActions(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
private:
    void split(const std::string& s,const std::string& delim,std::vector<int>* ret);
private:
    std::vector<int> _vecTags;
};

#endif
