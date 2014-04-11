
#include "acts.h"

using namespace cocos2d;
using namespace cocostudio;


IMPLEMENT_CLASS_INFO(PlayMusic)
PlayMusic::PlayMusic(void)
:_tag(-1)
{
}

PlayMusic::~PlayMusic(void)
{
}

bool PlayMusic::init()
{
    return true;
}

void PlayMusic::done()
{
	do 
	{
		Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
		CC_BREAK_IF(node == nullptr);
		ComAudio *audio = (ComAudio*)(node->getComponent(_comName.c_str()));
		CC_BREAK_IF(audio == nullptr);
		if (_type == 0)
		{
			audio->playBackgroundMusic();
		}
		else if (_type == 1)
		{
			audio->playEffect();
		}

	} while (0);
}

void PlayMusic::serialize(const rapidjson::Value &val)
{
	int count = DICTOOL->getArrayCount_json(val, "dataitems");
	for (int i = 0; i < count; ++i)
	{
		const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "dataitems", i);
		std::string key = DICTOOL->getStringValue_json(subDict, "key");
		if (key == "Tag")
		{
			_tag = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "componentName")
		{
			_comName = DICTOOL->getStringValue_json(subDict, "value");
			continue;
		}
		else if (key == "type")
		{
			_type = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
	}
}

void PlayMusic::removeAll()
{
}

IMPLEMENT_CLASS_INFO(TMoveTo)
TMoveTo::TMoveTo(void)
:_tag(-1)
,_duration(0.0f)
{
}

TMoveTo::~TMoveTo(void)
{
}

bool TMoveTo::init()
{
	return true;
}

void TMoveTo::done()
{
	do 
	{
		Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
		CC_BREAK_IF(node == nullptr);
		ActionInterval*  actionTo = MoveTo::create(_duration, _pos);
		CC_BREAK_IF(actionTo == nullptr);
		node->runAction(actionTo);
	} while (0);
}

void TMoveTo::serialize(const rapidjson::Value &val)
{
	int count = DICTOOL->getArrayCount_json(val, "dataitems");
	for (int i = 0; i < count; ++i)
	{
		const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "dataitems", i);
		std::string key = DICTOOL->getStringValue_json(subDict, "key");
		if (key == "Tag")
		{
			_tag = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "Duration")
		{
			_duration = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "x")
		{
			_pos.x = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "y")
		{
			_pos.y = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
	}
}

void TMoveTo::removeAll()
{
	Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
	node->getActionManager()->removeAllActions();
}

IMPLEMENT_CLASS_INFO(TMoveBy)
TMoveBy::TMoveBy(void)
:_tag(-1)
,_duration(0.0f)
,_reverse(false)
{
}

TMoveBy::~TMoveBy(void)
{
}

bool TMoveBy::init()
{
    return true;
}

void TMoveBy::done()
{
	do 
	{
		Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
		CC_BREAK_IF(node == nullptr);
		ActionInterval*  actionBy = MoveBy::create(_duration, _pos);
		CC_BREAK_IF(actionBy == nullptr);
		if (_reverse == true)
		{
			ActionInterval*  actionByBack = actionBy->reverse();
            if (_repeatForever)
            {
                node->runAction(RepeatForever::create(static_cast<Sequence *>(Sequence::create(actionBy, actionByBack,nullptr))));  
            }
            else
            {
                node->runAction(Sequence::create(actionBy, actionByBack, nullptr));
            }
			
		}
		else
		{
			node->runAction(actionBy);
		}
	} while (0);
}

void TMoveBy::serialize(const rapidjson::Value &val)
{
	int count = DICTOOL->getArrayCount_json(val, "dataitems");
	for (int i = 0; i < count; ++i)
	{
		const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "dataitems", i);
		std::string key = DICTOOL->getStringValue_json(subDict, "key");
		if (key == "Tag")
		{
			_tag = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "Duration")
		{
			_duration = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "x")
		{
			_pos.x = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "y")
		{
			_pos.y = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "IsReverse")
		{
			_reverse = DICTOOL->getIntValue_json(subDict, "value") ? true : false;
			continue;
		}
        else if (key == "IsRepeatForever")
        {
            _repeatForever = (DICTOOL->getIntValue_json(subDict, "value") == 1);
            continue;
        }
	}
}

void TMoveBy::removeAll()
{
    Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
	node->getActionManager()->removeAllActions();
}



IMPLEMENT_CLASS_INFO(TRotateTo)
TRotateTo::TRotateTo(void)
: _tag(-1)
, _duration(0.0f)
, _deltaAngle(0.0f)
{
}

TRotateTo::~TRotateTo(void)
{
}

bool TRotateTo::init()
{
    return true;
}

void TRotateTo::done()
{
	do 
	{
		Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
		CC_BREAK_IF(node == nullptr);
		ActionInterval*  actionTo = RotateTo::create(_duration, _deltaAngle);
		CC_BREAK_IF(actionTo == nullptr);
		node->runAction(actionTo);
	} while (0);
}

void TRotateTo::serialize(const rapidjson::Value &val)
{
	int count = DICTOOL->getArrayCount_json(val, "dataitems");
	for (int i = 0; i < count; ++i)
	{
		const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "dataitems", i);
		std::string key = DICTOOL->getStringValue_json(subDict, "key");
		if (key == "Tag")
		{
			_tag = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "Duration")
		{
			_duration = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "DeltaAngle")
		{
			_deltaAngle = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
	}
}

void TRotateTo::removeAll()
{
	Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
	node->getActionManager()->removeAllActions();
}



IMPLEMENT_CLASS_INFO(TRotateBy)
TRotateBy::TRotateBy(void)
: _tag(-1)
, _duration(0.0f)
, _deltaAngle(0.0f)
, _reverse(false)
{
}

TRotateBy::~TRotateBy(void)
{
}

bool TRotateBy::init()
{
    return true;
}

void TRotateBy::done()
{
	do 
	{
		Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
		CC_BREAK_IF(node == nullptr);
		ActionInterval*  actionBy = RotateBy::create(_duration, _deltaAngle);
		CC_BREAK_IF(actionBy == nullptr);
		if (_reverse == true)
		{
			ActionInterval*  actionByBack = actionBy->reverse();
            if (_repeatForever)
            {
                node->runAction(RepeatForever::create(static_cast<Sequence *>(Sequence::create(actionBy, actionByBack,nullptr))));  
            }
            else
            {
                node->runAction(Sequence::create(actionBy, actionByBack, nullptr));
            }
			
		}
		else
		{
			node->runAction(actionBy);
		}
	} while (0);
}

void TRotateBy::serialize(const rapidjson::Value &val)
{
	int count = DICTOOL->getArrayCount_json(val, "dataitems");
	for (int i = 0; i < count; ++i)
	{
		const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "dataitems", i);
		std::string key = DICTOOL->getStringValue_json(subDict, "key");
		if (key == "Tag")
		{
			_tag = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "Duration")
		{
			_duration = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "DeltaAngle")
		{
			_deltaAngle = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "IsReverse")
		{
			_reverse = (DICTOOL->getIntValue_json(subDict, "value")) ? true : false;
			continue;
		}
        else if (key == "IsRepeatForever")
        {
            _repeatForever = (DICTOOL->getIntValue_json(subDict, "value") == 1);
            continue;
        }
	}
}

void TRotateBy::removeAll()
{
    Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
	node->getActionManager()->removeAllActions();
}



IMPLEMENT_CLASS_INFO(TScaleTo)
TScaleTo::TScaleTo(void)
: _tag(-1)
, _duration(0.0f)
{
}

TScaleTo::~TScaleTo(void)
{
}

bool TScaleTo::init()
{
    return true;
}

void TScaleTo::done()
{
	do 
	{
		Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
		CC_BREAK_IF(node == nullptr);
		ActionInterval*  actionTo = ScaleTo::create(_duration, _scale.x, _scale.y);
		CC_BREAK_IF(actionTo == nullptr);
		node->runAction(actionTo);
	} while (0);
}

void TScaleTo::serialize(const rapidjson::Value &val)
{
	int count = DICTOOL->getArrayCount_json(val, "dataitems");
	for (int i = 0; i < count; ++i)
	{
		const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "dataitems", i);
		std::string key = DICTOOL->getStringValue_json(subDict, "key");
		if (key == "Tag")
		{
			_tag = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "Duration")
		{
			_duration = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "ScaleX")
		{
			_scale.x = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "ScaleY")
		{
			_scale.y = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
	}
}

void TScaleTo::removeAll()
{
	Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
	node->getActionManager()->removeAllActions();
}



IMPLEMENT_CLASS_INFO(TScaleBy)
TScaleBy::TScaleBy(void)
: _tag(-1)
, _duration(0.0f)
, _reverse(false)
{
}

TScaleBy::~TScaleBy(void)
{
}

bool TScaleBy::init()
{
    return true;
}

void TScaleBy::done()
{
	do 
	{
		Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
		CC_BREAK_IF(node == nullptr);
		ActionInterval*  actionBy = ScaleBy::create(_duration, _scale.x, _scale.y);
		CC_BREAK_IF(actionBy == nullptr);
		if (_reverse == true)
		{
			ActionInterval*  actionByBack = actionBy->reverse();
            if (_repeatForever)
            {
                node->runAction(RepeatForever::create(static_cast<Sequence *>(Sequence::create(actionBy, actionByBack,nullptr))));  
            }
            else
            {
                node->runAction(Sequence::create(actionBy, actionByBack, nullptr));
            }
			
		}
		else
		{
			node->runAction(actionBy);
		}
	} while (0);
}

void TScaleBy::serialize(const rapidjson::Value &val)
{
	int count = DICTOOL->getArrayCount_json(val, "dataitems");
	for (int i = 0; i < count; ++i)
	{
		const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "dataitems", i);
		std::string key = DICTOOL->getStringValue_json(subDict, "key");
		if (key == "Tag")
		{
			_tag = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "Duration")
		{
			_duration = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "ScaleX")
		{
			_scale.x = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "ScaleY")
		{
			_scale.y = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "IsReverse")
		{
			_reverse = (DICTOOL->getIntValue_json(subDict, "value")) ? true : false;
			continue;
		}
        else if (key == "IsRepeatForever")
        {
            _repeatForever = (DICTOOL->getIntValue_json(subDict, "value") == 1);
            continue;
        }
	}
}

void TScaleBy::removeAll()
{
	Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
	node->getActionManager()->removeAllActions();
}



IMPLEMENT_CLASS_INFO(TSkewTo)
TSkewTo::TSkewTo(void)
: _tag(-1)
, _duration(0.0f)
{
}

TSkewTo::~TSkewTo(void)
{
}

bool TSkewTo::init()
{
    return true;
}

void TSkewTo::done()
{
	do 
	{
		Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
		CC_BREAK_IF(node == nullptr);
		ActionInterval*  actionTo = SkewTo::create(_duration, _skew.x, _skew.y);
		CC_BREAK_IF(actionTo == nullptr);
		node->runAction(actionTo);
	} while (0);
}

void TSkewTo::serialize(const rapidjson::Value &val)
{
	int count = DICTOOL->getArrayCount_json(val, "dataitems");
	for (int i = 0; i < count; ++i)
	{
		const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "dataitems", i);
		std::string key = DICTOOL->getStringValue_json(subDict, "key");
		if (key == "Tag")
		{
			_tag = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "Duration")
		{
			_duration = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "SkewX")
		{
			_skew.x = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "SkewY")
		{
			_skew.y = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
	}
}

void TSkewTo::removeAll()
{
	Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
	node->getActionManager()->removeAllActions();
}



IMPLEMENT_CLASS_INFO(TSkewBy)
TSkewBy::TSkewBy(void)
: _tag(-1)
, _duration(0.0f)
, _reverse(false)
{
}

TSkewBy::~TSkewBy(void)
{
}

bool TSkewBy::init()
{
    return true;
}

void TSkewBy::done()
{
	do 
	{
		Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
		CC_BREAK_IF(node == nullptr);
		ActionInterval*  actionBy = SkewBy::create(_duration, _skew.x, _skew.y);
		CC_BREAK_IF(actionBy == nullptr);
		if (_reverse == true)
		{
			ActionInterval*  actionByBack = actionBy->reverse();
            if (_repeatForever)
            {
                node->runAction(CCRepeatForever::create(static_cast<Sequence *>(Sequence::create(actionBy, actionByBack,nullptr))));  
            }
            else
            {
                node->runAction(Sequence::create(actionBy, actionByBack, nullptr));
            }
			node->runAction(Sequence::create(actionBy, actionByBack, nullptr));
		}
		else
		{
			node->runAction(actionBy);
		}
	} while (0);
}

void TSkewBy::serialize(const rapidjson::Value &val)
{
	int count = DICTOOL->getArrayCount_json(val, "dataitems");
	for (int i = 0; i < count; ++i)
	{
		const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "dataitems", i);
		std::string key = DICTOOL->getStringValue_json(subDict, "key");
		if (key == "Tag")
		{
			_tag = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "Duration")
		{
			_duration = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "SKewX")
		{
			_skew.x = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "SKewY")
		{
			_skew.y = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "IsReverse")
		{
			_reverse = DICTOOL->getIntValue_json(subDict, "value") ? true : false;
		}
        else if (key == "IsRepeatForever")
        {
            _repeatForever = (DICTOOL->getIntValue_json(subDict, "value") == 1);
            continue;
        }
	}
}

void TSkewBy::removeAll()
{
	Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
	node->getActionManager()->removeAllActions();
}



IMPLEMENT_CLASS_INFO(TriggerState)
TriggerState::TriggerState(void)
{
    _id = -1;
    _state = 0;
}

TriggerState::~TriggerState(void)
{
}

bool TriggerState::init()
{
    return true;
}

void TriggerState::done()
{
    TriggerObj *obj = TriggerMng::getInstance()->getTriggerObj(_id);
	if (obj != nullptr)
	{
		if (_state == 0)
		{
			obj->setEnabled(false);
		}
		else if (_state == 1)
		{
			obj->setEnabled(true);
		}
		else if (_state == 2)
		{
			TriggerMng::getInstance()->removeTriggerObj(_id);
		}
		
	}
	
}

void TriggerState::serialize(const rapidjson::Value &val)
{
	int count = DICTOOL->getArrayCount_json(val, "dataitems");
	for (int i = 0; i < count; ++i)
	{
		const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "dataitems", i);
		std::string key = DICTOOL->getStringValue_json(subDict, "key");
		if (key == "ID")
		{
			_id = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "State")
		{
			_state = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
	}
}

void TriggerState::removeAll()
{
	CCLOG("TriggerState::removeAll");
}

IMPLEMENT_CLASS_INFO(ArmaturePlayAction)
ArmaturePlayAction::ArmaturePlayAction(void)
: _tag(-1)
{
}

ArmaturePlayAction::~ArmaturePlayAction(void)
{
}

bool ArmaturePlayAction::init()
{
	return true;
}

void ArmaturePlayAction::done()
{
	do 
	{
		Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
		CC_BREAK_IF(node == nullptr);
		ComRender *pRender = (ComRender*)(node->getComponent(_comName.c_str()));
		CC_BREAK_IF(pRender == nullptr);
		Armature *pAr = (Armature *)(pRender->getNode());
		CC_BREAK_IF(pAr == nullptr);
		pAr->getAnimation()->play(_aniname.c_str());
	} while (0);
}

void ArmaturePlayAction::serialize(const rapidjson::Value &val)
{
	int count = DICTOOL->getArrayCount_json(val, "dataitems");
	for (int i = 0; i < count; ++i)
	{
		const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "dataitems", i);
		std::string key = DICTOOL->getStringValue_json(subDict, "key");
		if (key == "Tag")
		{
			_tag = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "componentName")
		{
			_comName = DICTOOL->getStringValue_json(subDict, "value");
			continue;
		}
		else if (key == "AnimationName")
		{
			_aniname = DICTOOL->getStringValue_json(subDict, "value");
			continue;
		}
	}
}

void ArmaturePlayAction::removeAll()
{
	CCLOG("ArmaturePlayAction::removeAll");
}



IMPLEMENT_CLASS_INFO(SequenceMoveTo)
SequenceMoveTo::SequenceMoveTo(void)
{
}

SequenceMoveTo::~SequenceMoveTo(void)
{
}

bool SequenceMoveTo::init()
{
    return true;
}

void SequenceMoveTo::done()
{
    do 
    {
        Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
        CC_BREAK_IF(node == nullptr);
        MoveTo* pEndAction = CCMoveTo::create(_endDur, _endPos);
        MoveTo* pStartAction = CCMoveTo::create(_startDur, _startPos);

        Sequence* action = nullptr;
        if (_delayTime < 0)
        {
            action = Sequence::create(pEndAction, pStartAction, nullptr);
        }
        else
        {
            action = Sequence::create(DelayTime::create(_delayTime), pEndAction, pStartAction, nullptr);
        } 
        if (!_repeatForever)
        {
            node->runAction(action);
        }
        else
        {
            node->runAction(CCRepeatForever::create(action));
        }
    } while (0);
}

void SequenceMoveTo::serialize(const rapidjson::Value &val)
{
    int count = DICTOOL->getArrayCount_json(val, "dataitems");
	for (int i = 0; i < count; ++i)
	{
		const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "dataitems", i);
		std::string key = DICTOOL->getStringValue_json(subDict, "key");
		if (key == "Tag")
		{
			_tag = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "EndX")
		{
			_endPos.x = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "EndY")
		{
			_endPos.y = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "EndDuration")
		{
			_endDur = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "StartX")
		{
			_startPos.x = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "StartY")
		{
			_startPos.y = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "StartDuration")
		{
			_startDur = DICTOOL->getFloatValue_json(subDict, "value");
			continue;
		}
		else if (key == "DelayTime")
		{
			_delayTime = DICTOOL->getFloatValue_json(subDict, "value");
		}
		else if (key == "IsRepeatForever")
		{
			_repeatForever = (DICTOOL->getIntValue_json(subDict, "value") == 1);
			continue;
		}
	}
}

void SequenceMoveTo::removeAll()
{
    Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
    node->getActionManager()->removeAllActions();
}



IMPLEMENT_CLASS_INFO(JumpAction)
JumpAction::JumpAction(void)
{
}

JumpAction::~JumpAction(void)
{
}

bool JumpAction::init()
{
    return true;
}

void JumpAction::done()
{
    do 
    {
        Node *node = SceneReader::getInstance()->getNodeByTag(_tag);
        CC_BREAK_IF(node == nullptr);
        node->setRotation(_rotationTo);
        MoveTo *pAction = MoveTo::create(_riseTime, ccp(node->getPositionX(), node->getPositionY() + _riseHeight)); 
        node->stopAllActions();  
        node->runAction(Spawn::create(  
            Sequence::create(pAction, DelayTime::create(_jumpDelayTime), nullptr), nullptr)  
            );
    } while (0);
}

void JumpAction::serialize(const rapidjson::Value &val)
{
    int count = DICTOOL->getArrayCount_json(val, "dataitems");
    for (int i = 0; i < count; ++i)
    {
        const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "dataitems", i);
        std::string key = DICTOOL->getStringValue_json(subDict, "key");
        if (key == "Tag")
        {
            _tag = DICTOOL->getIntValue_json(subDict, "value");
            continue;
        }
        else if (key == "RiseHeight")
        {
            _riseHeight = DICTOOL->getFloatValue_json(subDict, "value");
            continue;
        }
        else if (key == "RiseTime")
        {
            _riseTime = DICTOOL->getFloatValue_json(subDict, "value");
            continue;
        }
        else if (key == "JumpDelayTime")
        {
            _jumpDelayTime = DICTOOL->getFloatValue_json(subDict, "value");
            continue;
        }
        else if (key == "RotationTo")
        {
            _rotationTo = DICTOOL->getFloatValue_json(subDict, "value");
            continue;
        }
    }
}

void JumpAction::removeAll()
{
	CCLOG("JumpAction::removeAll");
}



IMPLEMENT_CLASS_INFO(FallAction)
FallAction::FallAction(void)
{
}

FallAction::~FallAction(void)
{
}

bool FallAction::init()
{
    return true;
}

void FallAction::done()
{
    do 
    {
        Node *pNode = SceneReader::getInstance()->getNodeByTag(_tag);
        CC_BREAK_IF(pNode == nullptr);
        pNode->stopAllActions();    
        float postionX = pNode->getPositionX();  
        float postionY = pNode->getPositionY();  
        float time = postionY / _fallSpeed;  
        pNode->runAction(Sequence::create( 
            Spawn::create(RotateTo::create(time, _rotationTo), MoveTo::create(time, ccp(postionX, _fallTo)), nullptr), nullptr)  
            );  

    } while (0);
}

void FallAction::serialize(const rapidjson::Value &val)
{
    int count = DICTOOL->getArrayCount_json(val, "dataitems");
    for (int i = 0; i < count; ++i)
    {
        const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "dataitems", i);
        std::string key = DICTOOL->getStringValue_json(subDict, "key");
        if (key == "Tag")
        {
            _tag = DICTOOL->getIntValue_json(subDict, "value");
            continue;
        }
        else if (key == "FallTimeParam")
        {
            _fallSpeed = DICTOOL->getFloatValue_json(subDict, "value");
            continue;
        }
        else if (key == "RotationTo")
        {
            _rotationTo = DICTOOL->getFloatValue_json(subDict, "value");
            continue;
        }
        else if (key == "FallTo")
        {
            _fallTo = DICTOOL->getFloatValue_json(subDict, "value");
            continue;
        }
    }
}

void FallAction::removeAll()
{
	CCLOG("FallAction::removeAll");
}



IMPLEMENT_CLASS_INFO(ChangeDoubleAttribute)
ChangeDoubleAttribute::ChangeDoubleAttribute(void)
{
}

ChangeDoubleAttribute::~ChangeDoubleAttribute(void)
{
}

bool ChangeDoubleAttribute::init()
{
    return true;
}

void ChangeDoubleAttribute::done()
{
    do 
    {
        CCNode *pNode = SceneReader::getInstance()->getNodeByTag(_tag);
        CC_BREAK_IF(pNode == NULL);
        ComAttribute *attri = static_cast<ComAttribute*>(pNode->getComponent("CCComAttribute"));
        float value = attri->getFloat(_key.c_str());
        if (_type == 0)
        {
            value -= _value;

        }
        else if (_type == 1)
        {
            value = _value;
        }
        else
        {
            value += _value;
        }

        if (_limit == 0)
        {
            if (value < 0)
            {
                value = 0;
            }
        }
        else if (_limit == 1)
        {
            if (value > 0)
            {
                value = 0;
            }
        }

        attri->setFloat("UpSpeed", value);

    } while (0);
}

void ChangeDoubleAttribute::serialize(const rapidjson::Value &val)
{
    int count = DICTOOL->getArrayCount_json(val, "dataitems");
    for (int i = 0; i < count; ++i)
    {
        const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "dataitems", i);
        std::string key = DICTOOL->getStringValue_json(subDict, "key");
        if (key == "Tag")
        {
            _tag = DICTOOL->getIntValue_json(subDict, "value");
            continue;
        }
        else if (key == "Key")
        {
            _key = DICTOOL->getStringValue_json(subDict, "value");
            continue;
        }
        else if (key == "Value")
        {
            _value = DICTOOL->getFloatValue_json(subDict, "value");
            continue;
        }
        else if (key == "ChangeType")
        {
            _type = DICTOOL->getIntValue_json(subDict, "value");
            continue;
        }
        else if (key == "Limit")
        {
            _limit = DICTOOL->getIntValue_json(subDict, "value");
            continue;
        }
    }
}

void ChangeDoubleAttribute::removeAll()
{
	CCLOG("ChangeDoubleAttribute::removeAll");
}



IMPLEMENT_CLASS_INFO(AddAccToPositionY)
AddAccToPositionY::AddAccToPositionY(void)
{
}

AddAccToPositionY::~AddAccToPositionY(void)
{
}

bool AddAccToPositionY::init()
{
    return true;
}

void AddAccToPositionY::done()
{
    do 
    {
        CCNode *pNode = SceneReader::getInstance()->getNodeByTag(_tag);
        CC_BREAK_IF(pNode == nullptr);
        ComAttribute *attri = dynamic_cast<ComAttribute*>(pNode->getComponent(_comName.c_str()));
        CC_BREAK_IF(attri == nullptr);
        float value = attri->getFloat(_key.c_str());
        attri->setFloat(_key.c_str(), value + _acceleration * CCDirector::getInstance()->getDeltaTime());
        value = pNode->getPositionY() - attri->getFloat(_key.c_str());

        float t = attri->getFloat("Acceleration");
        pNode->setPositionY(value);
    } while (0);
}

void AddAccToPositionY::serialize(const rapidjson::Value &val)
{
    int count = DICTOOL->getArrayCount_json(val, "dataitems");
    for (int i = 0; i < count; ++i)
    {
        const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "dataitems", i);
        std::string key = DICTOOL->getStringValue_json(subDict, "key");
        if (key == "Tag")
        {
            _tag = DICTOOL->getIntValue_json(subDict, "value");
            continue;
        }
        else if (key == "ComName")
        {
            _comName = DICTOOL->getStringValue_json(subDict, "value");
            continue;
        }
        else if (key == "Key")
        {
            _key = DICTOOL->getStringValue_json(subDict, "value");
            continue;
        }
        else if (key == "Acceleration")
        {
            _acceleration = DICTOOL->getFloatValue_json(subDict, "value");
            continue;
        }
    }
}

void AddAccToPositionY::removeAll()
{
	CCLOG("AddAccToPositionY::removeAll");
}



IMPLEMENT_CLASS_INFO(SequenceMoveToAndChangePositionY)
SequenceMoveToAndChangePositionY::SequenceMoveToAndChangePositionY(void)
{
}

SequenceMoveToAndChangePositionY::~SequenceMoveToAndChangePositionY(void)
{
}

bool SequenceMoveToAndChangePositionY::init()
{
    return true;
}

void SequenceMoveToAndChangePositionY::done()
{
    do 
    {
        Node *pNode = SceneReader::getInstance()->getNodeByTag(_tag);
        CC_BREAK_IF(pNode == NULL);
        int y = getRandNum(_minPositionY, _maxPositionY);
        pNode->setPositionY(y);
        _endPos.y = y;
        CCMoveTo* pEndAction = CCMoveTo::create(_endDur, _endPos);
        _startPos.y = y;
        CCMoveTo* pStartAction = CCMoveTo::create(_startDur, _startPos);
        CCAction* pAction = NULL;

        if (_delayTime < 0)
        {
            pAction = Sequence::create(pEndAction, pStartAction, CCCallFuncND::create(this, callfuncND_selector(SequenceMoveToAndChangePositionY::actionOver), pNode), NULL);  
        }
        else
        {
            pAction = Sequence::create(CCDelayTime::create(_delayTime), pEndAction, pStartAction, CCCallFuncND::create(this, callfuncND_selector(SequenceMoveToAndChangePositionY::actionOver), pNode), NULL);  
        } 

        pNode->runAction(pAction);
    } while (0);
}

void SequenceMoveToAndChangePositionY::serialize(const rapidjson::Value &val)
{
    int count = DICTOOL->getArrayCount_json(val, "dataitems");
    for (int i = 0; i < count; ++i)
    {
        const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "dataitems", i);
        std::string key = DICTOOL->getStringValue_json(subDict, "key");
        if (key == "Tag")
        {
            _tag = DICTOOL->getIntValue_json(subDict, "value");
            continue;
        }
        else if (key == "EndX")
        {
            _endPos.x = DICTOOL->getIntValue_json(subDict, "value");
            continue;
        }
        else if (key == "EndDuration")
        {
            _endDur = DICTOOL->getFloatValue_json(subDict, "value");
            continue;
        }
        else if (key == "StartX")
        {
            _startPos.x = DICTOOL->getIntValue_json(subDict, "value");
            continue;
        }
        else if (key == "StartDuration")
        {
            _startDur = DICTOOL->getFloatValue_json(subDict, "value");
            continue;
        }
        else if (key == "DelayTime")
        {
            _delayTime = DICTOOL->getFloatValue_json(subDict, "value");
        }
        else if (key == "MaxPositonY")
        {
            _maxPositionY =  DICTOOL->getIntValue_json(subDict, "value");
        }
        else if (key == "MinPositonY")
        {
            _minPositionY =  DICTOOL->getIntValue_json(subDict, "value");
        }
    }
}

void SequenceMoveToAndChangePositionY::removeAll()
{
    Node *pNode = SceneReader::getInstance()->getNodeByTag(_tag);
    pNode->getActionManager()->removeAllActions();
}

int SequenceMoveToAndChangePositionY::getRandNum(int min, int max)
{
    float i = CCRANDOM_0_1()*(max - min + 1) + min; 
    return (int)i; 
}

void SequenceMoveToAndChangePositionY::actionOver(Node* pSender, void* data)
{
    CCNode *pNode = (CCNode*)data;
    CCSequence *pAction = NULL;

    int y = getRandNum(_minPositionY, _maxPositionY);
    pNode->setPositionY(y);
    _endPos.y = y;
    MoveTo* pEndAction = MoveTo::create(_endDur, _endPos);
    _startPos.y = y;
    MoveTo* pStartAction = MoveTo::create(_startDur, _startPos);
    pAction = Sequence::create(pEndAction, pStartAction, CCCallFuncND::create(this, callfuncND_selector(SequenceMoveToAndChangePositionY::actionOver), pNode), nullptr);  
    pNode->runAction(pAction);

    return;
}

IMPLEMENT_CLASS_INFO(SetNodeVisible)
SetNodeVisible::SetNodeVisible(void)
{
}

SetNodeVisible::~SetNodeVisible(void)
{
}

bool SetNodeVisible::init()
{
    return true;
}

void SetNodeVisible::done()
{
    do 
    {
        CCNode *pNode = SceneReader::getInstance()->getNodeByTag(_tag);
        CC_BREAK_IF(pNode == NULL);
        pNode->setVisible(_show);
    } while (0);
}

void SetNodeVisible::serialize(const rapidjson::Value &val)
{
    int count = DICTOOL->getArrayCount_json(val, "dataitems");
    for (int i = 0; i < count; ++i)
    {
        const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "dataitems", i);
        std::string key = DICTOOL->getStringValue_json(subDict, "key");
        if (key == "Tag")
        {
            _tag = DICTOOL->getIntValue_json(subDict, "value");
            continue;
        }
        else if (key == "Visible")
        {
            _show = DICTOOL->getIntValue_json(subDict, "value") == 1;
            continue;
        }
    }
}

void SetNodeVisible::removeAll()
{
	CCLOG("SetNodeVisible::removeAll");
}



IMPLEMENT_CLASS_INFO(PlayUIAnimation)
PlayUIAnimation::PlayUIAnimation(void)
{
}

PlayUIAnimation::~PlayUIAnimation(void)
{
}

bool PlayUIAnimation::init()
{
    return true;
}

void PlayUIAnimation::done()
{
    ActionManagerEx::getInstance()->playActionByName(_uiJsonName.c_str(), _animaitionName.c_str());
}

void PlayUIAnimation::serialize(const rapidjson::Value &val)
{
    int count = DICTOOL->getArrayCount_json(val, "dataitems");
    for (int i = 0; i < count; ++i)
    {
        const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "dataitems", i);
        std::string key = DICTOOL->getStringValue_json(subDict, "key");
        if (key == "UIJsonName")
        {
            _uiJsonName = DICTOOL->getStringValue_json(subDict, "value");
            continue;
        }
        else if (key == "AnimationName")
        {
            _animaitionName = DICTOOL->getStringValue_json(subDict, "value");
            continue;
        }
    }
}

void PlayUIAnimation::removeAll()
{
	CCLOG("PlayUIAnimation::removeAll");
}



IMPLEMENT_CLASS_INFO(StopAllActions)
StopAllActions::StopAllActions(void)
{
}

StopAllActions::~StopAllActions(void)
{
}

bool StopAllActions::init()
{
    return true;
}

void StopAllActions::done()
{
    do 
    {
        for (std::vector<int>::iterator iter = _vecTags.begin(); iter != _vecTags.end(); ++iter)
        {
            CCNode *pNode = SceneReader::getInstance()->getNodeByTag(*iter);
            if (pNode == NULL)
            {
                continue;;
            }
            pNode->stopAllActions();
        }
    } while (0);
}

void StopAllActions::serialize(const rapidjson::Value &val)
{
    int count = DICTOOL->getArrayCount_json(val, "dataitems");
    for (int i = 0; i < count; ++i)
    {
        const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "dataitems", i);
        std::string key = DICTOOL->getStringValue_json(subDict, "key");
        if (key == "Tags")
        {
            std::string strTags = DICTOOL->getStringValue_json(subDict, "value");
            split(strTags, ",", &_vecTags);
            continue;
        }
    }
}

void StopAllActions::removeAll()
{
	CCLOG("StopAllActions::removeAll");
}

void StopAllActions::split(const std::string& s,const std::string& delim,std::vector<int>* ret)
{
    size_t last = 0;
    size_t index=s.find_first_of(delim,last);
    while (index!=std::string::npos)
    {
        ret->push_back(atoi(s.substr(last,index-last).c_str()));
        last=index+1;
        index=s.find_first_of(delim,last);
    }
    if (index-last>0)
    {
        ret->push_back(atoi(s.substr(last,index-last).c_str()));
    }
}


