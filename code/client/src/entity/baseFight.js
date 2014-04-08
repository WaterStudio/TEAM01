/**
 * Created by WaterStudio on 2014/4/8.
 * 战斗基础实体
 * 记录战斗数值
 * PS:下划线开头的函数定义为私有函数，不能在其它类中直接调用
 */
var ws = ws || {};
ws.BaseFightEntity = ws.BaseEntity.extend({
    _atk: 0,//攻击力
    _def: 0,//防御力
    _speed: 0,//速度
    _hp: 0,//血量
    ctor: function () {
        this._super();
    },
    setAtk: function (value) {
        this._atk = value;
    },
    getAtk: function () {
        return this._atk;
    },
    setDef: function (value) {
        this._def = value;
    },
    getDef: function () {
        return this._def;
    },
    setSpeed: function (value) {
        this._speed = value;
    },
    getSpeed: function () {
        return this._speed;
    },
    setHP: function (value) {
        this._hp = value;
    },
    getHP: function () {
        return this._hp;
    }
});