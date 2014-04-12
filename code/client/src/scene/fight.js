/**
 * Created by WaterStudio on 2014/4/8.
 */
var ws = ws || {};
ws.FightScene = cc.Scene.extend({
    _monster_timer: null,//怪物出兵计时器
    _soldier1_timer: null,//1号位士兵出兵计时器
    _soldier2_timer: null,//2号位士兵出兵计时器
    _soldier3_timer: null,//3号位士兵出兵计时器
    _soldier4_timer: null,//4号位士兵出兵计时器
    _soldier5_timer: null,//5号位士兵出兵计时器
    onEnter: function () {
        this._super();
        this.addChild(new ws.FightSceneLayer());
        this.addChild(new ws.UICommonMessageBox());

        this._monster_timer = new ws.TimerManager();
        this._monster_timer.tick(this.monsterTimerCallBack, this);
        this._monster_timer.start();
        //this._soldier1_timer=new ws.TimerManager();
        //ws.FightManager.getInstance().buildSoldier();

    },
    //每次执行创建一个怪物
    monsterTimerCallBack: function () {
        //this._monster_timer.setNextTick(1);
        ws.FightManager.getInstance().buildMonster();
    }
});
ws.FightSceneLayer = cc.Layer.extend({
    _main_scene_node: null,
    _main_ui_node: null,
    ctor: function () {
        this._super();
    },
    onEnter: function () {
        this._super();
        this.bindScene();
        this.bindMainUI();


    },
    bindScene: function () {
        //bind ui
        this._main_scene_node = ccs.sceneReader.createNodeWithSceneFile(res.cocostudio.battle.battle_scene_json);
        this._main_scene_node.setLocalZOrder(1);
        this.addChild(this._main_scene_node);
        //init animation
       // ccs.actionManager.playActionByName("Battle_Send_Stone.ExportJson", "StoneAnimation");
    },
    bindMainUI: function () {
        //bind ui
        this._main_ui_node = ccs.uiReader.widgetFromJsonFile(res.cocostudio.battle.ui.battle_main_ui.battle_main_ui_exportjson);
        this._main_ui_node.setLocalZOrder(2);
        this.addChild(this._main_ui_node);
        for (var i = 0; i < 5; i++) {
            //bind event
            var button = ccui.helper.seekWidgetByName(this._main_ui_node, "Soldier_Select_" + (i + 1) + "_Button");
            button.addTouchEventListener(this.touchEvent, this);
            //init animation
            ccs.actionManager.playActionByName("Battle_Main_UI.ExportJson", "Select_" + (i + 1) + "_Lock");
        }
    },
    touchEvent: function (sender, type) {
        switch (type) {
            case ccui.Widget.TOUCH_BAGAN:
                cc.log("Touch Down");
                break;
            case ccui.Widget.TOUCH_MOVED:
                cc.log("Touch Move");
                break;
            case ccui.Widget.TOUCH_ENDED:
                cc.log("Touch Up");
                break;
            case ccui.Widget.TOUCH_CANCELED:
                cc.log("Touch Cancelled");
                break;
            default:
                break;
        }
    }
});
