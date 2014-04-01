var exec = require('child_process').exec;
var async = require('async');

/* Synchronous version of scriptRunner.js
 *
 */
console.time('total Execution Time');
var tasks = [];
var cmds = [
  './unordered_dither mad256.pgm 8 .5 out1.pgm',
  './ordered_dither mad256.pgm 3 .5 out2.pgm',
  './ordered_dither mad256.pgm 4 .5 out3.pgm',
  './ordered_dither mad256.pgm 8 .5 out4.pgm',
  './halftone eye50.pgm 4 .4 out5.pgm',
  './halftone eye50.pgm 8 .4 out6.pgm',
  './error_diffusion mad256.pgm 1 1 .5 out8.pgm',
  './blur mandrill256.pgm 5 5 out9.pgm',
  './blur mandrill256.pgm 5 1 out10.pgm',
  './blur mandrill256.pgm 1 5 out11.pgm',
  './sharpen mad256.pgm 5 3 out12.pgm',
  './median maddot.pgm 3 0 out13.pgm',
  './convolve mad256.pgm file1.AF out14.pgm',
  './convolve mad256.pgm file2.AF out15.pgm',
  './convolve mad256.pgm file3.AF out16.pgm',
  './convolve mad256.pgm file4.AF out17.pgm'
];

// Generate exec function from each command
cmds.forEach(function(data) {
    tasks.push(function(callback) {
    exec(data, function(error, stdout, stderr) {
      console.log(stdout);
      callback(null);
    });
  });
});

// Wrap 'exec' function inside a async.waterfall which ensures that 'make' is executed beforehand.

//console.time('Series execution Time');
async.series(tasks, function(err, results) {
  //console.timeEnd('Series execution Time');
  console.timeEnd('total Execution Time');
});


