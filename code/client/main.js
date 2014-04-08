cc.game.onStart = function () {
    cc.view.setDesignResolutionSize(800, 450, cc.ResolutionPolicy.SHOW_ALL);
    cc.view.resizeWithBrowserSize(true);
    //load resources
    cc.LoaderScene.preload(g_resources, function () {
        //cc.director.runScene(new HelloWorldScene());
        ws.AppEnter.getInstance().run();
    }, this);
};
cc.game.run();
var pomelo = window.pomelo;
var host = "127.0.0.1";
var port = "3010";
function show() {
    pomelo.init({
        host: host,
        port: port,
        log: true
    }, function () {
        pomelo.request("connector.entryHandler.entry", "hello pomelo", function (data) {
            console.log(data.msg);
        });
    });
}