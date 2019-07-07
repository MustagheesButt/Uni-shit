var selected = [];
var selectedStayDurations = [];

$('input[name="destinations[]"]').on('change', function () {
    var index = selected.indexOf(this);
    if (index == -1) {
        selected.push(this);
        selectedStayDurations.push(1);
    } else {
        selected.splice(index, 1); // remove using index
        selectedStayDurations.splice(index, 1);
    }

    /* Update UI */
    // clears the UI, so it is easy to maintain order
    $('.selected-destinations').html('');
    $('.selected-destinations-stay-duration').html('');

    selected.forEach(function (value, index) {
        $('.selected-destinations').append('<tr><td>' + $(value).next().html() + '</td><td><input class="bind-from" type="number" value="' + selectedStayDurations[index] + '" min="0" /></td></tr>');
        $('.selected-destinations-stay-duration').append('<input class="bind-to" type="number" value="' + selectedStayDurations[index] + '" min="0" name="stay_durations[]" />')
    });

    // update total cost and travel time
    $.post('http://localhost:5000/get-cost', {destinations: get_values(selected)}, function (response) {
        console.log(response)
        $('.total-cost').html(response);
    });
    $.post('http://localhost:5000/get-travel-time', {destinations: get_values(selected)}, function (response) {
        console.log(response)
        $('.total-travel-time').html(response);
    });
});

// screening
$('#next').on('click', function (e) {
    e.preventDefault();

    $('.screen-1').fadeOut(function () {
       $('.screen-2').fadeIn();
    });
});

// data binder for stay durations
// uses delegate events since the input elements are dynamically added
$(document).on('input change', 'input.bind-from', function () {
    var index = $('.bind-from').index($(this));
    var newValue = $(this).val();

    selectedStayDurations[index] = newValue;
    $($('.bind-to')[index]).val(newValue);
});

function get_values(arr) {
    var values = [];

    arr.forEach(function (val, index) {
       values.push($(val).val());
    });

    return values;
}
