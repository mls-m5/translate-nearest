

var textarea = document.getElementById("abc");
var output = document.getElementById("output");

String.prototype.replaceAll = function(search, replacement) {
    var target = this;
    return target.split(search).join(replacement);
};

function change() {
    var str = textarea.value;
    str = str.replaceAll("\n", "%0A");
    str = str.replaceAll(" ", "%20");
    $.get("translate.php?text=" + str, function(ret) {
        output.innerHTML = ret;
    });
}

textarea.addEventListener("keyup", change);