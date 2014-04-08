/**
 * Created by WaterStudio on 2014/4/8.
 * 通用组建-信息框
 */
ws.UICommonMessageBox = cc.Layer.extend({
    ctor: function () {
        this._super();
        this.setVisible(false);//default
    },
    show: function () {
        this.setVisible(true);
    }
});