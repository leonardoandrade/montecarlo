#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <emscripten/emscripten.h>
#include <unistd.h>
#include "model.h"

#define CANVAS_ID  "canvas"

//function reset_webpage() 
EM_JS(void, reset_webpage, (), {
    const field1 = document.getElementById('pointsInside');
    field1.innerHTML = "";
    const field2 = document.getElementById('pointsOutside');
    field2.innerHTML = "";
    const canvas  = document.getElementById("canvas");
    const context = canvas.getContext('2d');
    context.clearRect(0, 0, canvas.width, canvas.height);
    const centerX = canvas.width / 2;
    const centerY = canvas.height / 2;
    const radius  = canvas.height / 2;
  
    context.beginPath();
    context.arc(centerX, centerY, radius, 0, 2 * Math.PI, false);
    context.fillStyle = '#ADD8E6';
    context.fill();
});

//function update_webpage(dom) 
EM_JS(void, update_webpage, (int x, int y, int pointsInside, int pointsOutside, double pi) , {
    
    const field1 = document.getElementById('pointsInside');
    field1.innerHTML = "" +  pointsInside;
    const field2 = document.getElementById('pointsOutside');
    field2.innerHTML = "" + pointsOutside;
    const field3 = document.getElementById('pi');
    field3.innerHTML = "" + pi;

    console.log("Canvas updated, point = [%d, %d, %f]", x, y, pi);
    const ctx = document.getElementById("canvas").getContext("2d");
    ctx.fillStyle = "rgba(200, 100, 100, 0.5)";
    ctx.beginPath(); 
    ctx.arc(x, y, 1, 0, Math.PI * 2, true);
    ctx.fill(); 
    
});

