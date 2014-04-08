/**
 * Created by WaterStudio on 2014/4/8.
 */
var ws = ws || {};
ws.ContainerManager = cc.Class.extend({
    _container: {},//容器
    ctor: function () {

    },
    addObject: function (key, value) {
        this._container[key] = value;
    },
    removeObject: function () {
        delete this._container[key];
    },
    getObject: function (key) {
        return this._container[key] || null;
    },
    getObjects: function () {
        return this._container;
    }
});