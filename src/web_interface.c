#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <emscripten/emscripten.h>
#include <unistd.h>
#include "model.h"

#define CANVAS_ID  "canvas"

//function reset_webpage() 
EM_JS(void, reset_webpage, (int sideSize), {
    function drawCanvas (suffix) {
        const field1 = document.getElementById('pointsInside' + suffix);
        field1.innerHTML = "";
        const field2 = document.getElementById('pointsOutside' + suffix);
        field2.innerHTML = "";
        const canvas  = document.getElementById("canvas" + suffix);
        canvas.width= sideSize;
        canvas.height= sideSize;
    
        const context = canvas.getContext('2d');
        context.clearRect(0, 0, sideSize, sideSize);
        const centerX = sideSize / 2;
        const centerY = sideSize / 2;
        const radius  = sideSize / 2;
  
        context.beginPath();
        context.arc(centerX, centerY, radius, 0, 2 * Math.PI, false);
        context.fillStyle = '#ADD8E6';
        context.fill();
    }
    drawCanvas("_quasi_random");
    drawCanvas("_pseudo_random");
});

//function update_webpage(dom) 
EM_JS(void, update_webpage, (
                             int x_quasi, int y_quasi, int pointsInside_quasi, int pointsOutside_quasi, double pi_quasi,
                             int x_pseudo, int y_pseudo, int pointsInside_pseudo, int pointsOutside_pseudo, double pi_pseudo
                            ), {
    function drawCanvas (suffix, x, y, pointsInside, pointsOutside, pi) {
        const field1 = document.getElementById('pointsInside' + suffix);
        field1.innerHTML = "" +  pointsInside;
        const field2 = document.getElementById('pointsOutside' + suffix);
        field2.innerHTML = "" + pointsOutside;
        const field3 = document.getElementById('pi' + suffix);
        field3.innerHTML = "" + pi;

        const field4 = document.getElementById('pi_divergence' + suffix);
        const delta = Math.round((Math.PI - pi) * 10000) / 10000;
        field4.innerHTML = "" + delta;

        //console.log("Canvas updated, point = [%d, %d, %f]", x, y, pi);
        const ctx = document.getElementById("canvas" + suffix).getContext("2d");
        ctx.fillStyle = "rgba(200, 0, 0, 0.7)";
        ctx.beginPath(); 
        ctx.arc(x, y, 1, 0, Math.PI * 2, true);
        ctx.fill(); 
    }
    drawCanvas("_quasi_random", x_quasi, y_quasi, pointsInside_quasi, pointsOutside_quasi, pi_quasi);
    drawCanvas("_pseudo_random", x_pseudo, y_pseudo, pointsInside_pseudo, pointsOutside_pseudo, pi_pseudo);
});

