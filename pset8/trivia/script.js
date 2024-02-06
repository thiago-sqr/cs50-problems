document.addEventListener('DOMContentLoaded', function() {
                
    let correct = document.querySelector('.correct');
    correct.addEventListener('click', function() {
        correct.style.backgroundColor = 'MediumSeaGreen';
        document.querySelector('#part1_result').innerHTML = "Correct!";
    });

    let incorrect = document.querySelectorAll('.incorrect');
    for (let i = 0; i < incorrect.length; i++) {
        incorrect[i].addEventListener('click', function() {
            incorrect[i].style.backgroundColor = 'Tomato';
            document.querySelector('#part1_result').innerHTML = "Incorrect!";
        });
    }

    let answer = document.querySelector('#submit');
    answer.addEventListener('click', function() {
        city = document.querySelector('#townName').value;
        city = city.toLowerCase();
        if (city === 'nuvema' || city === 'nuvema town') {
            document.querySelector('#part2_result').innerHTML = "Correct!";
            document.querySelector('#townName').style.backgroundColor = 'MediumSeaGreen';
        }
        else {
            document.querySelector('#part2_result').innerHTML = "Incorrect!";
            document.querySelector('#townName').style.backgroundColor = 'Tomato';
        }
    });
});