document.addEventListener('DOMContentLoaded', function() {
    
    starters = document.querySelectorAll('.pagelink');

    for(let i = 0; i < starters.length; i++) {

        starters[i].addEventListener('mouseover', function() {
            starters[i].style.textDecoration = 'underline';
        });

        starters[i].addEventListener('mouseout', function() {
            starters[i].style.textDecoration = 'none';
        });
    }
});