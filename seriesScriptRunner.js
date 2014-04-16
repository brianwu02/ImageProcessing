var exec = require('child_process').exec;
var async = require('async');

/* Synchronous version of scriptRunner.js
 *
 */
console.time('total Execution Time');
var tasks = [];

 var cmds = [
  './unordered_dither images/mad256.pgm 8 .5 output/out1.pgm',
  './ordered_dither images/mad256.pgm 3 .5 output/out2.pgm',
  './ordered_dither images/mad256.pgm 4 .5 output/out3.pgm',
  './ordered_dither images/mad256.pgm 8 .5 output/out4.pgm',
  './halftone images/eye50.pgm 4 .4 output/out5.pgm',
  './halftone images/eye50.pgm 8 .4 output/out6.pgm',
  './error_diffusion images/mad256.pgm 1 1 .5 output/out8.pgm',
  './blur images/mandrill256.pgm 5 5 output/out9.pgm',
  './blur images/mandrill256.pgm 5 1 output/out10.pgm',
  './blur images/mandrill256.pgm 1 5 output/out11.pgm',
  './sharpen images/mad256.pgm 5 3 output/out12.pgm',
  './median images/maddot.pgm 3 0 output/out13.pgm',
  './convolve images/mad256.pgm file1.AF output/out14.pgm',
  './convolve images/mad256.pgm file2.AF output/out15.pgm',
  './convolve images/mad256.pgm file3.AF output/out16.pgm',
  './convolve images/mad256.pgm file4.AF output/out17.pgm'
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


