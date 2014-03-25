var spawn = require('child_process').spawn;
var exec = require('child_process').exec;
var async = require('async');
/* Series of commands to run
  unordered_dither mad256.pgm 8 .5 out1.pgm
  ordered_dither mad256.pgm 3 .5 out2.pgm
  ordered_dither mad256.pgm 4 .5 out3.pgm
  ordered_dither mad256.pgm 8 .5 out4.pgm
  halftone eye50.pgm 4 .4 out5.pgm
  halftone eye50.pgm 8 .4 out6.pgm
  error_diffusion mad256.pgm 0 1 .5 out7.pgm
  error_diffusion mad256.pgm 1 1 .5 out8.pgm
  blur mandrill256.pgm 5 5 out9.pgm
  blur mandrill256.pgm 5 1 out10.pgm
  blur mandrill256.pgm 1 5 out11.pgm
  sharpen mad256.pgm 5 3 out12.pgm
  median maddot.pgm 3 0 out13.pgm
  convolve mad256.pgm file1.AF out14.pgm
  convolve mad256.pgm file2.AF out15.pgm
  convolve mad256.pgm file3.AF out16.pgm
  convolve mad256.pgm file4.AF out17.pgm
*/

async.parallel([
  function() {
  exec('./unordered_dither mad256.pgm 8 .5 out1.pgm',
       function(error, stdout, stderr) {
         console.log("STDOUT: " + stdout);
       });
}, function() {
  exec('./ordered_dither mad256.pgm 3 .5 out2.pgm',
       function(error, stdout, stderr) {
         console.log("STDOUT: " + stdout);
       });
}, function() {
  exec('./ordered_dither mad256.pgm 4 .5 out3.pgm',
       function(error, stdout, stderr) {
         console.log("STDOUT: " + stdout);
       });
}, function() {
  exec('./ordered_dither mad256.pgm 8 .5 out4.pgm',
       function(error, stdout, stderr) {
         console.log("STDOUT: " + stdout);
       });
}, function() {
  exec('./halftone eye50.pgm 4 .4 out5.pgm',
       function(error, stdout, stderr) {
         console.log("STDOUT: " + stdout);
       });
}, function() {
  exec('./halftone eye50.pgm 8 .4 out6.pgm',
       function(error, stdout, stderr) {
         console.log("STDOUT: " + stdout);
       });
}, function() {
  exec('./error_diffusion mad256.pgm 0 1 out7.pgm',
       function(error, stdout, stderr) {
         console.log("STDOUT: " + stdout);
       });
}, function() {
  exec("cat 'this second error diffusion not working yet'",
       function(error, stdout, stderr) {
         console.log("STDOUT: " + stdout);
       });
}, function() {
  exec('./blur mandrill256.pgm 5 5 out9.pgm',
       function(error, stdout, stderr) {
         console.log("STDOUT: " + stdout);
       });
}, function() {
  exec('./blur mandrill256.pgm 5 1 out10.pgm',
       function(error, stdout, stderr) {
         console.log("STDOUT: " + stdout);
       });
}, function() {
  exec('./blur mandrill256.pgm 1 5 out11.pgm',
       function(error, stdout, stderr) {
         console.log("STDOUT: " + stdout);
       });
}, function() {
  exec('./median maddot.pgm 3 0 out13.pgm',
       function(error, stdout, stderr) {
         console.log("STDOUT: " + stdout);
       });
}, function() {
  exec('./convolve mad256.pgm file1.AF out14.pgm',
       function(error, stdout, stderr) {
         console.log("STDOUT: " + stdout);
       });
}, function() {
  exec('./convolve mad256.pgm file2.AF out15.pgm',
       function(error, stdout, stderr) {
         console.log("STDOUT: " + stdout);
       });
}, function() {
  exec('./convolve mad256.pgm file3.AF out16.pgm',
       function(error, stdout, stderr) {
         console.log("STDOUT: " + stdout);
       });
}, function() {
  exec('./convolve mad256.pgm file4.AF out17.pgm',
       function(error, stdout, stderr) {
         console.log("STDOUT: " + stdout);
       });
}]);

/*
var blur = spawn('./blur', [
  'mad256.pgm', '5', '5', 'out5.pgm']);
var unordered_dither = spawn('./unordered_dither', [
  'mad256.pgm', '8', '.5', 'out1.pgm']);
*/


/*
blur.stdout.on('data', function(data) {
  console.log('stdout:' + data);
});

blur.stderr.on('data', function(data) {
  console.log(data);
});

blur.on('close', function(code) {
  console.log('code: ' + code);
});
*/

/*
ls.stdout.on('data', function(data) {
  console.log('stdout: ' + data);
});

ls.stderr.on('data', function(data) {
  console.log('stderr: ' + data);
});

ls.on('close', function(code) {
  console.log('child process exited with code' + code);
});
*/





