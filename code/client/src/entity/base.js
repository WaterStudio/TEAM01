/**
 * Created by WaterStudio on 2014/4/8.
 * 基础实体类
 * 记录名称、尺寸等基础数据
 * PS:下划线开头的函数定义为私有函数，不能在其它类中直接调用
 */
var ws = ws || {};
ws.BaseEntity = cc.Class.extend({
    _id: 0,//标识
    _name: "",//对象名称
    _width: 0,//对象宽度
    _height: 0,//对象高度
    ctor: function () {
        this._super();
        this._id = ClassManager.getNewID();
    },
    //----------------需要重写[start]-----------------
    init: function (json) {
    },
    //----------------需要重写[end]-----------------
    setName: function (name) {
        this._name = name;
    },
    getName: function () {
        return this._name;
    },
    getId: function () {
        return this._id;
    },
    getWidth: function () {
        return this._width;
    },
    getHeight: function () {
        return this._height;
    }
});