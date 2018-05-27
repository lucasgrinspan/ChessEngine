var pieces = document.getElementsByClassName("piece");
var board =    [[' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
                [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
                [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
                [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
                [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
                [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
                [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
                [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ']];
//  Reads board from application into array
for (var i = 0; i < pieces.length; i++) {
    var tileNumber = parseInt(pieces[i].parentElement.id.slice(5));
    var pieceIcon = pieces[i].id;
    board[Math.floor(tileNumber / 8)][tileNumber % 8] = pieceIcon;
}
for (var i = 0; i < 8; i++) {
    var boardString = "";
    for (var j = 0; j < 8; j++) {
        boardString += (board[i][j] + " ");
    }
    console.log(boardString);
    boardString = "";
}