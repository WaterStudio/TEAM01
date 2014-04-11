
#include "cons.h"

using namespace cocos2d;
using namespace cocostudio;


IMPLEMENT_CLASS_INFO(TimeElapsed)

TimeElapsed::TimeElapsed(void)
:_totalTime(0.0f)
,_tmpTime(0.0f)
,_scheduler(nullptr)
,_suc(false)
{
	_scheduler = Director::getInstance()->getScheduler();
	_scheduler->retain();
}

TimeElapsed::~TimeElapsed(void)
{
	CC_SAFE_RELEASE(_scheduler);
}

bool TimeElapsed::init()
{
	_scheduler->schedule(schedule_selector(TimeElapsed::update), this, 0.0f , kRepeatForever, 0.0f, false);
    return true;
}

bool TimeElapsed::detect()
{
    return _suc;
}

void TimeElapsed::serialize(const rapidjson::Value &val)
{
    int count = DICTOOL->getArrayCount_json(val, "dataitems");
	for (int i = 0; i < count; ++i)
	{
		const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "dataitems", i);
		std::string key = DICTOOL->getStringValue_json(subDict, "key");
		if (key == "TotalTime")
		{
			_totalTime = DICTOOL->getFloatValue_json(subDict, "value");
		}
	}
}

void TimeElapsed::removeAll()
{
	_scheduler->unschedule(schedule_selector(TimeElapsed::update), this);
}

void TimeElapsed::update(float dt)
{
	_tmpTime += dt;
	if (_tmpTime > _totalTime)
	{
		_tmpTime = 0.0f;
		_suc = true;
	}
}

IMPLEMENT_CLASS_INFO(ArmatureActionState)
ArmatureActionState::ArmatureActionState(void)
: _tag(-1)
, _state(-1)
, _suc(false)
{
}

ArmatureActionState::~ArmatureActionState(void)
{
}

bool ArmatureActionState::init()
{
	do 
	{
		Node *pNode = SceneReader::getInstance()->getNodeByTag(_tag);
		CC_BREAK_IF(pNode == nullptr);
		ComRender *pRender = (ComRender*)(pNode->getComponent(_comName.c_str()));
		CC_BREAK_IF(pRender == nullptr);
		Armature *pAr = (Armature *)(pRender->getNode());
		CC_BREAK_IF(pAr == nullptr);
		TriggerMng::getInstance()->addArmatureMovementCallBack(pAr, this, movementEvent_selector(ArmatureActionState::animationEvent));
	} while (0);
	
	return true;
}

bool ArmatureActionState::detect()
{
    return _suc;
}

void ArmatureActionState::serialize(const rapidjson::Value &val)
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
		else if (key == "ActionType")
		{
			_state = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
	}
}

void ArmatureActionState::removeAll()
{
	do 
	{
		Node *pNode = SceneReader::getInstance()->getNodeByTag(_tag);
		CC_BREAK_IF(pNode == nullptr);
		ComRender *pRender = (ComRender*)(pNode->getComponent(_comName.c_str()));
		CC_BREAK_IF(pRender == nullptr);
		Armature *pAr = (Armature *)(pRender->getNode());
		CC_BREAK_IF(pAr == nullptr);
		TriggerMng::getInstance()->removeArmatureMovementCallBack(pAr, this, movementEvent_selector(ArmatureActionState::animationEvent));
	} while (0);
}

void ArmatureActionState::animationEvent(cocostudio::Armature *armature, cocostudio::MovementEventType movementType, const std::string& movementID)
{
	 std::string id = movementID;
	if (movementType == _state && id.compare(_aniname) == 0)
	{
		_suc = true;
	}
}

IMPLEMENT_CLASS_INFO(NodeInRect)
NodeInRect::NodeInRect(void)
:_tag(-1)
{
}

NodeInRect::~NodeInRect(void)
{
}

bool NodeInRect::init()
{

    return true;
}

bool NodeInRect::detect()
{
	Node *pNode = SceneReader::getInstance()->getNodeByTag(_tag);
	if (pNode != nullptr && abs(pNode->getPositionX() - _origin.x) <= _size.width && abs(pNode->getPositionY() - _origin.y) <= _size.height)
	{
		return true;
	}
    return false;
}

void NodeInRect::serialize(const rapidjson::Value &val)
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
		else if (key == "originX")
		{
			_origin.x = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "originY")
		{
			_origin.y = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "sizeWidth")
		{
			_size.width = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
		else if (key == "sizeHeight")
		{
			_size.height = DICTOOL->getIntValue_json(subDict, "value");
			continue;
		}
	}
}

void NodeInRect::removeAll()
{
	CCLOG("NodeInRect::removeAll");
}


IMPLEMENT_CLASS_INFO(NodeVisible)
NodeVisible::NodeVisible(void)
: _tag(-1)
, _visible(false)
{
}

NodeVisible::~NodeVisible(void)
{
}

bool NodeVisible::init()
{
	return true;
}

bool NodeVisible::detect()
{
	Node *pNode = SceneReader::getInstance()->getNodeByTag(_tag);
	if (pNode != nullptr && pNode->isVisible() == _visible)
	{
		return true;
	}
	return false;
}

void NodeVisible::serialize(const rapidjson::Value &val)
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
			_visible = DICTOOL->getIntValue_json(subDict, "value") ? true : false;
			continue;
		}
	}
}

void NodeVisible::removeAll()
{
	CCLOG("NodeVisible::removeAll");
}






IMPLEMENT_CLASS_INFO(RectangleCollisionTest)
RectangleCollisionTest::RectangleCollisionTest(void)
{
}

RectangleCollisionTest::~RectangleCollisionTest(void)
{
}

bool RectangleCollisionTest::init()
{
    return true;
}

bool RectangleCollisionTest::detect()
{
    do 
    {
        Node *pNodeA = SceneReader::getInstance()->getNodeByTag(_tag_A);
        CC_BREAK_IF(pNodeA == NULL);
        Node *pComNodeA = pNodeA;
        if (SceneReader::getInstance()->getAttachComponentType() == SceneReader::AttachComponentType::EMPTY_NODE)
        {
            pComNodeA = getNode(pNodeA, _comName_A);
        }
        CC_BREAK_IF(pComNodeA == NULL);
        for (std::vector<int>::iterator iter = _vecTags.begin(); iter != _vecTags.end(); ++iter)
        {
            Node *pNodeB = SceneReader::getInstance()->getNodeByTag(*iter);
            CC_BREAK_IF(pNodeB == NULL);
            Node *pComNodeB = pNodeB;
            if (SceneReader::getInstance()->getAttachComponentType() == SceneReader::AttachComponentType::EMPTY_NODE)
            {
                pComNodeB = getNode(pNodeB, _comName_B);
                CC_BREAK_IF(pComNodeB == NULL);
            }
            Point p1 = pNodeA->getPosition();
            Point p2 =  pNodeB->getParent()->getPosition() + pNodeB->getPosition();

            Rect ARect(p1.x, p1.y, pComNodeA->getContentSize().width + _aOffsetX, pComNodeA->getContentSize().height + _aOffsetY);
            Rect BRect(p2.x, p2.y, pComNodeB->getContentSize().width + _bOffsetX, pComNodeB->getContentSize().height + _bOffsetY);
            if (isRectCollision(ARect, BRect))
            {
                CCLOG("peng!!!");
                return true;
            }
        }
    } while (0);

    return false;
}

void RectangleCollisionTest::serialize(const rapidjson::Value &val)
{
    int count = DICTOOL->getArrayCount_json(val, "dataitems");
    for (int i = 0; i < count; ++i)
    {
        const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "dataitems", i);
        std::string key = DICTOOL->getStringValue_json(subDict, "key");
        if (key == "Tag_A")
        {
            _tag_A = DICTOOL->getIntValue_json(subDict, "value");
            continue;
        }
        else if (key == "ComName_A")
        {
            _comName_A = DICTOOL->getStringValue_json(subDict, "value");
            continue;
        }
        if (key == "AOffsetX")
        {
            _aOffsetX = DICTOOL->getFloatValue_json(subDict, "value");
            continue;
        }
        else if (key == "AOffsetY")
        {
            _aOffsetY = DICTOOL->getFloatValue_json(subDict, "value");
            continue;
        }
        else if (key == "Tags")
        {
            std::string strTags = DICTOOL->getStringValue_json(subDict, "value");
            split(strTags, ",", &_vecTags);
            continue;
        }
        else if (key == "ComName_B")
        {
            _comName_B = DICTOOL->getStringValue_json(subDict, "value");
            continue;
        }
        if (key == "BOffsetX")
        {
            _bOffsetX = DICTOOL->getFloatValue_json(subDict, "value");
            continue;
        }
        else if (key == "BOffsetY")
        {
            _bOffsetY = DICTOOL->getFloatValue_json(subDict, "value");
            continue;
        }
    }
}

void RectangleCollisionTest::removeAll()
{
    CCLOG("RectangleCollisionTest::removeAll");
}

bool RectangleCollisionTest::isRectCollision(Rect rect1, Rect rect2)
{
    float x1 = rect1.origin.x;
    float y1 = rect1.origin.y;
    float w1 = rect1.size.width;
    float h1 = rect1.size.height;
    float x2 = rect2.origin.x;
    float y2 = rect2.origin.y;
    float w2 = rect2.size.width;
    float h2 = rect2.size.height;

    if (fabs(x1 - x2) > (w1 * 0.5 + w2 * 0.5) || fabs(y1 - y2) > (h1 * 0.5 + h2 * 0.5))
    {
        return false;
    }

    return true;
}

cocos2d::CCNode* RectangleCollisionTest::getNode(cocos2d::Node *pNode, std::string comName)
{
    do 
    {
        CC_BREAK_IF(pNode == NULL);
        Component *com = pNode->getComponent(comName.c_str());
        CC_BREAK_IF(com == NULL);
        ComRender *render = dynamic_cast<ComRender*>(com);
        CC_BREAK_IF(render == NULL);
        return render->getNode();
    } while (0);
    return NULL;
}

void RectangleCollisionTest::split(const std::string& s,const std::string& delim,std::vector<int>* ret)
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