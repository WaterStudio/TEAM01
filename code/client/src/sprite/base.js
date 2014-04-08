/**
 * Created by WaterStudio on 2014/4/8.
 */
var ws = ws || {};
ws.BaseSprite = cc.Sprite.extend({
    _id: 0,//标识
    ctor: function () {
        this._super();
        this._id = ClassManager.getNewID();
    },
    getId: function () {
        return this._id;
    }
});