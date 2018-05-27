#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <emscripten/emscripten.h>
#include <unistd.h>
#include "model.h"

#define CANVAS_ID  "canvas"

//function reset_webpage() 
EM_JS(void, reset_webpage, (), {
    const field = document.getElementById('iterations');
    field.innerHTML = "";
    const canvas  = document.getElementById(CANVAS_ID);
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
EM_JS(void, update_webpage, (DOMState dom) , {
    const field = document.getElementById('pointsInside');
    field.innerHTML = "" + dom.pointsInside;
    const field = document.getElementById('pointsOutside');
    field.innerHTML = "" + dom.pointsOutside;
    
    console.log("Canvas updated, point = [%d, %d]", dom.lastPoint.x, dom.lastPoint.y);
    const ctx = document.getElementById("canvas").getContext("2d");
    ctx.fillStyle = "rgba(200, 100, 100, 0.5)";
    ctx.beginPath(); 
    ctx.arc(dom.lastPoint.x, dom.lastPointy, 1, 0, Math.PI * 2, true);
    ctx.fill(); 
});

