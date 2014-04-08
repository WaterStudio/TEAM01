/**
 * Created by Cynthia on 2014/4/8.
 */

var ws = ws || {};
ws.AppEnter = cc.Class.extend({
    ctor: function () {

    },
    run: function () {
        //default open fight scene
        cc.director.runScene(new ws.FightScene());
        //test socket io
        show();
    }
});
ws._app_enter_instance = null;
ws.AppEnter.getInstance = function () {
    if (!ws._app_enter_instance)
        ws._app_enter_instance = new ws.AppEnter();
    return ws._app_enter_instance;
};

