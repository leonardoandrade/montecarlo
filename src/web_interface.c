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
       
       const field1 = document.getElementById('samples');
        field1.innerHTML = "" + 0;

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

        context.beginPath();
        context.rect(0,0,sideSize, sideSize);
        context.strokeStyle = '#333333';
        context.stroke();
    }
    drawCanvas("_quasi_random");
    drawCanvas("_pseudo_random");
});

//function update_webpage(dom) 
EM_JS(void, update_webpage, (int samples,
                             double x_quasi, double y_quasi, double pi_quasi,
                             double x_pseudo, double y_pseudo, double pi_pseudo
                            ), {
    function drawCanvas (suffix, x, y, pi) {
        console.log("point '" + suffix +"' (" +x+ ", " +y + ")");
        const field1 = document.getElementById('samples');
        field1.innerHTML = "" + samples;
        
        const field3 = document.getElementById('pi' + suffix);
        field3.innerHTML =  pi;

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
    drawCanvas("_quasi_random", x_quasi, y_quasi, pi_quasi);
    drawCanvas("_pseudo_random", x_pseudo, y_pseudo, pi_pseudo);
});

