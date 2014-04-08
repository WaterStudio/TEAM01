/**
 * Created by WaterStudio on 2014/4/8.
 */
var ws = ws || {};
ws.ENTITY_TYPE_ENUM = {
    "FIGHT_SOLDIER": 1,
    "FIGHT_MONSTER": 2
};
ws.EntityManager = cc.Class.extend({
    _all: new ws.ContainerManager(),
    _classify: {},//分类管理器
    ctor: function () {
        this._super();
    },
    create: function (json, type) {
        //do something
        var entity = null;
        switch (type) {
            case ws.ENTITY_TYPE_ENUM.FIGHT_SOLDIER:
                entity = new ws.FightSoldierEntity();
                break;
            case ws.ENTITY_TYPE_ENUM.FIGHT_MONSTER:
                entity = new ws.FightMonsterEntity();
                break;
        }
        if (entity) {
            entity.init(json);//初始化绑定数据
            this._all.addObject(entity.getId(), entity);//向总列表添加实体
            //创建一个分类器
            if (!this._classify[type])
                this._classify[type] = new ws.ContainerManager();
            this._classify[type].addObject(entity.getId(), entity);//向分类列表添加实体
            return true;
        }
        return false;
    },
    //获取一个实体
    getEntity: function (key, type) {
        if (!this._classify[type])
            return this._all.getObject(key);
        else
            return this._classify[type].getObject(key);
    },
    //获取一个实体列表
    getEntities: function (type) {
        if (!this._classify[type])
            return this._all.getObjects();
        else
            return this._classify[type].getObjects();
    }
});
ws._entity_manager_instance = null;
ws.EntityManager.getInstance = function () {
    if (!ws._entity_manager_instance)
        ws._entity_manager_instance = new ws.EntityManager();
    return ws._entity_manager_instance;
};
