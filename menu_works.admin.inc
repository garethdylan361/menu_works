<?php

function menu_works_page($menu) {
	return theme('menu_works_page', array(
	'menu' => $menu,
	));
};

function render_sortable_menus($menus) {
		$result = "";
		foreach($menus['menus'] as $menu) {
		$result .= render_sortable_menu($menu);
		}
		return $result;
}

function render_sortable_menu_children($menu) {
	$result = '';
	if(count($menu['children']) > 0 ) $result .= '<ol class="dd-list">';
	foreach($menu['children'] as $cmenu) $result .= render_sortable_menu($cmenu);
	if(count($menu['children']) > 0 ) $result .= ' </ol>';
	return $result;
}

function render_sortable_menu($menu) {
	$result = '<li class="dd-item" mlid="' .$menu['menu']['mlid'].'"  plid="' .$menu['menu']['plid'].'"  data-id="' .$menu['menu']['weight'] .'">'.
			'<div class="dd-handle">'.
			'<table class="sortable-table">'.
				'<tbody>'.
					'<tr>'.
						'<td class="sortable-node-title">' . $menu['title'];

			$result .= '</td>';

						$result .= 
						/*'<td class="sortable-node"><a class="dd-nodrag" href="/admin/structure/menu/manage/'. $menu['menu']['mlid'].'/add">Add</a></td>'.*/
						'<td class="sortable-node"><a class="dd-nodrag" href="/admin/structure/menu/item/'. $menu['menu']['mlid'].'/edit">Edit</a></td>'.
						'<td class="sortable-node"><a class="dd-nodrag" href="/admin/structure/menu/item/'. $menu['menu']['mlid'].'/delete">Delete</a></td>'.
					'</tr>'.
				'</tbody>'.
			'</table>'.
			'</div>'.
			render_sortable_menu_children($menu).
		'</li>';
	return $result;
}

function render_menus($m) {
	$variables = array();
	$result = get_menu_items($m, 0);
	while($menu = $result->fetchAssoc()) {
		$variables['menus'][$menu['mlid']]['menu'] = $menu;
		$variables['menus'][$menu['mlid']]['title'] = get_sortable_menu_title_markup($menu);
		$variables['menus'][$menu['mlid']]['children'] = get_menu_children_vars($m, $menu['mlid']);
	}
	return $variables;
}

function get_sortable_menu_title_markup($item) {
	return t($item['link_title']);
}

function get_menu_items($m, $plid) {
	return db_select('menu_links', 'm')
    ->fields('m')
	->condition('menu_name', $m,'=')
    ->condition('plid', $plid,'=')
	 ->orderBy('weight', 'ASC')
    ->execute();
}
function get_menu_children_vars($m, $plid) {
	$vars = array();
    $result = get_menu_items($m, $plid);
	while($menu = $result->fetchAssoc()) {
		$vars[$menu['mlid']]['menu'] = $menu;
		$vars[$menu['mlid']]['title'] = get_sortable_menu_title_markup($menu);
		$vars[$menu['mlid']]['children'] = get_menu_children_vars($menu['mlid']);
	}
	return $vars;
}
