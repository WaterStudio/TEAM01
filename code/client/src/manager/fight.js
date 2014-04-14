/**
 * Created by WaterStudio on 2014/4/8.
 * 战斗管理类
 * 负责建立实体与精灵的关系，被战斗场景类调用
 */
ws.FightManager = cc.Class.extend({
    ctor: function () {
    },
    //生产士兵
    buildSoldier: function (node) {
        //加载资源
        ccs.armatureDataManager.addArmatureFileInfo(res.cocostudio.battle.role.role_01.role_01_exportjson);
        //走路动画开始
        var armature = ccs.Armature.create("Role_01");
        armature.getAnimation().play("role_01_walk");
        //armature.scale = 0.6;
        node.addChild(armature);
    },
    //生产怪物
    buildMonster: function () {

    }
});
ws._fight_manager_instance = null;
ws.FightManager.getInstance = function () {
    if (!ws._fight_manager_instance)
        ws._fight_manager_instance = new ws.FightManager();
    return ws._fight_manager_instance;
};