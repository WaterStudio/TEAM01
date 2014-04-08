/**
 * Created by WaterStudio on 2014/4/8.
 * 战斗精灵基础类
 * 负责战斗精灵的生成、基本动作的定义与操作
 * PS:下划线开头的函数定义为私有函数，不能在其它类中直接调用
 */
var ws = ws || {};
ws.BaseFightSprite = ws.BaseSprite.extend({
    _base_sprite: null,
    ctor: function () {
        this._super();
    },
    //-------------------需要重写[start]----------------
    //初始化表单，生成sprite对象
    init: function (json) {
    },
    //攻击动作
    atk: function () {
    },
    //死亡动作
    dead: function () {
    },
    //受到动作
    hurt: function () {
    },
    //走路动作
    walk: function () {
    },
    //-------------------需要重写[end]----------------
    //暂停精灵动作
    pauseSprite: function () {
        cc.director.getActionManager().pauseTarget(this);
    },
    //还原精灵动作
    resumeSprite: function () {
        cc.director.getActionManager().resumeTarget(this);
    }
});