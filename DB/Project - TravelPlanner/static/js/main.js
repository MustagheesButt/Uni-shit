/* Filter */
var filterItems = $('.filter-item');
$('.filter').on('change input', function () {
    var filterVal = $(this).val();

    for (var i = 0; i < filterItems.length; i++) {
        if ($(filterItems[i]).find('.filter-val').html().indexOf(filterVal) == -1) {
            $(filterItems[i]).css('display', 'none');
        } else {
            $(filterItems[i]).css('display', 'block');
        }
    }
});