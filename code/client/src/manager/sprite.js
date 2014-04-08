/**
 * Created by WaterStudio on 2014/4/8.
 */
var ws = ws || {};
ws.SPRITE_TYPE_ENUM = {
    "FIGHT_SOLDIER": 1,
    "FIGHT_MONSTER": 2,
    "FIGHT_SEND_STONE": 3
};
ws.SpriteManager = cc.Class.extend({
    _all: new ws.ContainerManager(),
    _classify: {},//分类管理器
    ctor: function () {
        this._super();
    },
    create: function (json, type) {
        //do something
        var sprite = null;
        switch (type) {
            case ws.SPRITE_TYPE_ENUM.FIGHT_SOLDIER:
                sprite = new ws.FightSoldierSprite();
                break;
            case ws.SPRITE_TYPE_ENUM.FIGHT_MONSTER:
                sprite = new ws.FightMonsterSprite();
                break;
            case ws.SPRITE_TYPE_ENUM.FIGHT_SEND_STONE:
                sprite = new ws.FightSendStoneSprite();
                break;
        }
        if (sprite) {
            sprite.init(json);//初始化绑定数据
            this._all.addObject(sprite.getId(), sprite);//向总列表添加精灵
            //创建一个分类器
            if (!this._classify[type])
                this._classify[type] = new ws.ContainerManager();
            this._classify[type].addObject(sprite.getId(), sprite);//向分类列表添加精灵
            return true;
        }
        return false;
    },
    //获取一个精灵
    getSprite: function (key, type) {
        if (!this._classify[type])
            return this._all.getObject(key);
        else
            return this._classify[type].getObject(key);
    },
    //获取一个精灵列表
    getSprites: function (type) {
        if (!this._classify[type])
            return this._all.getObjects();
        else
            return this._classify[type].getObjects();
    }
});
ws._sprite_manager_instance = null;
ws.SpriteManager.getInstance = function () {
    if (!ws._sprite_manager_instance)
        ws._sprite_manager_instance = new ws.SpriteManager();
    return ws._sprite_manager_instance;
};
