   <div id="list" class="dd">
    <ol class="dd-list">
      
       <li>
            <div>
            <table class="sortable-table">
            	<tr>
            		<th class="sortable-node-title">Title</th>
            	</tr>
            </table>
            </div>
        </li>
        
       
       <?php print $menus; ?>
        
    </ol>
</div>
<script>
	

jQuery('.dd').nestable({ })
jQuery('.dd').on('change', function() {
	var weight = 0;
	var items = new Array();
	
  jQuery(this).find('.dd-item').each(function() {
	 var mlid = jQuery(this).attr('mlid');
	 var parent = jQuery(this).parents(".dd-item").attr("mlid");
	 var plid = (parent != undefined) ? parent : 0;
	 items.push({mlid: mlid, weight: weight, plid: plid});
	 weight++;
  })
    

 jQuery.post('/menu_works/save', {'js': 1, menus: items}, function(data) {
	
  });
});


	
</script>