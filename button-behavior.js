popupVisible = false;
function displayPreferences() {
    popupVisible = true;
    var preferencesWindow = document.getElementById("preferences");
    preferencesWindow.style.display = "block";
    createDimmer();
}
function createDimmer() {
    var popupOverlay = document.getElementById("popup-overlay");
    popupOverlay.style.display = "block";
}
function clearDimmer() {
    var popupOverlay = document.getElementById("popup-overlay");
    popupOverlay.style.display = "none";   
}
function clearPopup() {
    if (popupVisible) {
        var preferencesWindow = document.getElementById("preferences");
        preferencesWindow.style.display = "none";
        clearDimmer();
        popupVisible = false;
    }
}
function blockClickProp() {
    if (!event) var event = window.event;
    event.cancelBubble = true;
    if (event.stopPropagation) event.stopPropagation();
}
function changeBoardColor() {
    var theme = event.target;
    console.log(theme);
    var color1;
    var color2;
    if (theme.id.indexOf("alt") >= 0) {
        color2 = document.defaultView.getComputedStyle(theme, null)["backgroundColor"];
        color1 = document.defaultView.getComputedStyle(theme.previousElementSibling, null)["backgroundColor"];
    } else {
        color1 = document.defaultView.getComputedStyle(theme, null)["backgroundColor"];;
        color2 = document.defaultView.getComputedStyle(theme.nexElementSibling, null)["backgroundColor"];;
    }
    var whiteTiles = document.getElementsByClassName("white-tile");
    var blackTiles = document.getElementsByClassName("black-tile");
    for (var i = 0; i < whiteTiles.length; i++) {
        whiteTiles[i].style.backgroundColor = color1;
        blackTiles[i].style.backgroundColor = color2;
    }
}